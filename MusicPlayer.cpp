#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <deque>
#include <Windows.h>
#include "MusicPlayer.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

MusicPlayer::MusicPlayer() {
	hWaveOut = NULL;
	waitEvent = CreateEvent(NULL, 0, 0, NULL);
	fp = NULL;
	//soundData = NULL;
	fileSize = 0;

	myWaveFileBlock = {};

	/*myWaveFileBlock = new WaveFileBlock[MAX_BUFFER_COUNT];
	for (int i = 0; i < MAX_BUFFER_COUNT; i++) {
		memset(&myWaveFileBlock[i].header, 0, sizeof(WAVEHDR));
		myWaveFileBlock[i].header.dwFlags = WHDR_DONE;
		myWaveFileBlock[i].data = new char[MAX_BUFFER_SIZE];
	}*/
}

MusicPlayer::~MusicPlayer() {
	if (hWaveOut != NULL) {
		waveOutClose(hWaveOut);
		hWaveOut = NULL;
	}

	CloseHandle(waitEvent);

	/*for (int i = 0; i < MAX_BUFFER_COUNT; i++) {
		delete[] myWaveFileBlock[i].data;
	}
	delete[] myWaveFileBlock;*/
}

int MusicPlayer::SetVolume(WORD leftChannel, WORD rightChannel) {
	if (hWaveOut == NULL) {
		return 1;
	}
	DWORD resultVolume = (DWORD)rightChannel << 16 + (DWORD)leftChannel;
	waveOutSetVolume(hWaveOut, resultVolume);
	return 0;
}

int MusicPlayer::OpenFile(const char* path) {
	fp = NULL;
	char type[4];
	DWORD chunkSize, subchunk1Size, sampleRate, byteRate, subchunk2Size;
	WORD audioFormat, numChannels, blockAlign, bitsPerSample;
	
	fp = fopen(path, "rb");
	if (!fp) {
		cout << "Error: Failed to open file" << endl;
		return 1;
	}

	fread(type, sizeof(char), 4, fp);
	if (strncmp(type, "RIFF", 4) != 0) {
		cout << "Error: Not RIFF format" << endl;
		return 1;
	}

	fread(&chunkSize, sizeof(DWORD), 1, fp);
	fread(type, sizeof(char), 4, fp);
	if (strncmp(type, "WAVE", 4) != 0) {
		cout << "Error: Not WAVE format" << endl;
		return 1;
	}

	fread(type, sizeof(char), 4, fp);
	if (strncmp(type, "fmt ", 4) != 0) {
		cout << "Error: Not fmt" << endl;
		return 1;
	}

	fread(&subchunk1Size, sizeof(DWORD), 1, fp);
	fread(&audioFormat, sizeof(WORD), 1, fp);
	fread(&numChannels, sizeof(WORD), 1, fp);
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	fread(&byteRate, sizeof(DWORD), 1, fp);
	fread(&blockAlign, sizeof(WORD), 1, fp);
	fread(&bitsPerSample, sizeof(WORD), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if (strncmp(type, "data", 4) != 0) {
		cout << "Error: Missing data" << endl;
	}

	fread(&subchunk2Size, sizeof(DWORD), 1, fp);

	cout << "Chunk Size: " << chunkSize << endl;
	cout << "Subchunk 1 Size: " << subchunk1Size << endl;
	cout << "Audio Format: " << audioFormat << endl;
	cout << "Number of Channels: " << numChannels << endl;
	cout << "Sample Rate: " << sampleRate << endl;
	cout << "Byte Rate: " << byteRate << endl;
	cout << "Block Align (bytes per sample): " << blockAlign << endl;
	cout << "Bits per Sample: " << bitsPerSample << endl;
	cout << "Subchunk 2 Size: " << subchunk2Size << endl;
	
	fileSize = 8 + chunkSize;

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.wBitsPerSample = bitsPerSample;
	waveFormat.nChannels = numChannels;
	waveFormat.nSamplesPerSec = sampleRate;
	waveFormat.nAvgBytesPerSec = byteRate;
	waveFormat.nBlockAlign = blockAlign;
	waveFormat.cbSize = 0;
	
	soundData = new char[fileSize - 44];
	size_t x = fread(soundData, sizeof(char), fileSize - 44, fp);
	if (x != fileSize - 44) {
		cout << "size not match!" << endl;
	}
	cout << x << endl;
	//waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, (DWORD_PTR)waveOutProc, (DWORD_PTR)this, CALLBACK_FUNCTION);
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, (DWORD_PTR)waitEvent, 0L, CALLBACK_EVENT);
	fclose(fp);
	return 0;
}

int MusicPlayer::PlayMusic() {
	if (!fp) {
		cout << "Error: File is not opened" << endl;
		return 1;
	}
	return 0;
}

int MusicPlayer::ClosePlayer() {
	int result = waveOutClose(hWaveOut);
	return result;
}

int MusicPlayer::Playback(int second) {
	DWORD startOffset = waveFormat.nAvgBytesPerSec * second;
	DWORD endOffset = fileSize - 44;
	if (startOffset >= endOffset) {
		return -1;
	}
	DWORD curOffset = startOffset;

	DWORD len = endOffset - startOffset;
	DWORD n, r;
	n = len / MAX_BUFFER_SIZE;
	r = len % MAX_BUFFER_SIZE;
	
	thread addBuffer(&MusicPlayer::AddWavToBuffer, this, startOffset, endOffset);
	thread playFromBuffer(&MusicPlayer::PlayWavFromBuffer, this, startOffset, endOffset);
	//thread unprepareHeader(&MusicPlayer::UnprepareHeader, this);
	addBuffer.join();
	playFromBuffer.join();
	//unprepareHeader.join();
	waveOutClose(hWaveOut);
	return 0;
}

void MusicPlayer::AddWavToBuffer(DWORD startOffset, DWORD endOffset) {
	DWORD curOffset = startOffset;

	DWORD len = endOffset - startOffset;
	DWORD n, r;
	n = len / MAX_BUFFER_SIZE;
	r = len % MAX_BUFFER_SIZE;

	for (DWORD i = 0; i <= n; i++) {
		DWORD bufLen = (i < n) ? MAX_BUFFER_SIZE : r;
		printf("add buffer %d\n", i);
		//cout << "addbuffer " << i << '\n';
		unique_lock<mutex> bufLock(bufferMut);
		bufCond.wait(bufLock, [this] { return bufferQueue.size() < MAX_BUFFER_COUNT; });
		WaveFileBlock wfb;
		memset(&wfb.header, 0, sizeof(WAVEHDR));
		//wfb.data = new char[bufLen];
		char* data = new char[bufLen];
		memcpy(data, soundData + curOffset, bufLen);
		curOffset += MAX_BUFFER_SIZE;
		wfb.header.lpData = data;
		wfb.header.dwBufferLength = bufLen;
		wfb.header.dwFlags = 0L;
		wfb.header.dwLoops = 1L;
		wfb.state = WAITING;
		bufferQueue.push_back(wfb);
		bufLock.unlock();
		bufCond.notify_all();
	}
	cout << "1::Done all buffer\n";
}

void MusicPlayer::PlayWavFromBuffer(DWORD startOffset, DWORD endOffset) {
	DWORD len = endOffset - startOffset;
	DWORD n, r;
	n = len / MAX_BUFFER_SIZE;
	r = len % MAX_BUFFER_SIZE;
	//SetEvent(waitEvent);
	//ResetEvent(waitEvent);
	for (int i = 0; i <= n; i++) {
		printf("player buffer %d\n", i);
		//cout << "play buffer " << i << '\n';
		unique_lock<mutex> bufLock(bufferMut);
		bufCond.wait(bufLock, [this] { return bufferQueue.size() > 0; });
		WaveFileBlock wfb = bufferQueue.front();
		/*cout << "Play Wav\n";
		bufferQueue.front().state = PLAYING;
		bufLock.unlock();
		bufCond.notify_all();
		unique_lock<mutex> playLock(playMut);
		playCond.wait(playLock, [this] { return playerState == DONE; });
		cout << "Can play wave\n";
		waveOutPrepareHeader(hWaveOut, &wfb.header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &wfb.header, sizeof(WAVEHDR));
		playerState = PLAYING;
		playLock.unlock();
		playCond.notify_all();*/
		waveOutPrepareHeader(hWaveOut, &wfb.header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &wfb.header, sizeof(WAVEHDR));
		
		if (WaitForSingleObject(waitEvent, INFINITE) != WAIT_OBJECT_0) {
			cout << "Error waiting for sound to finish\n";
		}
		else {
			cout << "Sound finished\n";
		}
		if (waveOutUnprepareHeader(hWaveOut, &wfb.header, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
			cout << "Error to unprepare header\n";
			headerToUnprepareQueue.push_back(wfb.header);
		}
		else {
			cout << "Unprepared header\n";
		}
		bufferQueue.pop_front();			// need release memory
		bufLock.unlock();
		bufCond.notify_all();
	}
	cout << "2::Done all playing\n";
	// SHOULD FIX: unprepare header hardcode reset
	while (headerToUnprepareQueue.size() > 0) {
		headerToUnprepareQueue.pop_front();
		/*headerToUnprepareQueue.front().dwFlags = WHDR_DONE;
		headerToUnprepareQueue.front().lpData = NULL;
		switch (waveOutUnprepareHeader(hWaveOut, &headerToUnprepareQueue.front(), sizeof(WAVEHDR))) {
		case MMSYSERR_NOERROR: {
			cout << "MMSYSERR_NOERROR\n";
			
			break;
		}
		case MMSYSERR_INVALHANDLE: {
			cout << "MMSYSERR_INVALHANDLE\n";
			break;
		}
		case MMSYSERR_NODRIVER: {
			cout << "MMSYSERR_NODRIVER\n";
			break;
		}
		case MMSYSERR_NOMEM: {
			cout << "MMSYSERR_NOMEM\n";
			break;
		}
		case WAVERR_STILLPLAYING: {
			cout << "WAVERR_STILLPLAYING\n";
			break;
		}
		}*/
	}
	waveOutReset(hWaveOut);
}

void MusicPlayer::UnprepareHeader() {
	
}

// Deprecated
int MusicPlayer::WaitForPlay(char* data, DWORD len) {
	int result;
	WaveFileBlock wfb;
	memset(&wfb.header, 0, sizeof(WAVEHDR));
	wfb.data = new char[len];
	memcpy(wfb.data, data, len);
	wfb.header.lpData = wfb.data;
	wfb.header.dwBufferLength = len;
	wfb.header.dwFlags = 0L;
	wfb.header.dwLoops = 1L;
	wfb.state = WAITING;
	while (true) {
		if (bufferMut.try_lock()) {
			cout << "buffer locked" << endl;
			cout << "Buffer size: " << bufferQueue.size() << endl;
			if (bufferQueue.size() < MAX_BUFFER_COUNT) {
				bufferQueue.push_back(wfb);
				cout << "Push block to buffer" << endl;
				bufferMut.unlock();
				cout << "buffer unlocked" << endl;
				break;
			}
			else {
				bufferMut.unlock();
				cout << "buffer unlocked" << endl;
			}
		}
		else {
			cout << "can't buffer lock since locked" << endl;
		}
	}
	//delete wfb.data;
	result = WriteToWave(data, len);
	return 0;
}

// Deprecated
int MusicPlayer::WriteToWave(char* data, DWORD len) {
	//int result;
	/*for (int i = 0; i < MAX_BUFFER_COUNT; i++) {
		if (myWaveFileBlock[i].header.dwFlags == WHDR_DONE) {

		}

	}*/
	while (true) {
		if (playMut.try_lock()) {
			cout << "write locked" << endl;
			while (true) {
				if (bufferMut.try_lock()) {
					cout << "buffer locked" << endl;
					WaveFileBlock wfb = bufferQueue.front();
					wfb.state = PLAYING;
					waveOutPrepareHeader(hWaveOut, &wfb.header, sizeof(WAVEHDR));
					//bufferQueue.pop();
					bufferMut.unlock();
					cout << "buffer unlocked" << endl;
					waveOutWrite(hWaveOut, &wfb.header, sizeof(WAVEHDR));
					cout << "play wave" << endl;
					break;
				}
			}
			//writeWaveLock.unlock();
			break;
		}
		else {
			cout << "can't write lock since locked" << endl;
		}
	}
	return 0;
}

// Deprecated
void CALLBACK MusicPlayer::waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) {
	MusicPlayer* thisPlayer = (MusicPlayer* )dwInstance;
	switch (uMsg) {
	case WOM_DONE: {
		cout << "DONE" << endl;
		/*unique_lock<mutex> playLock(thisPlayer->playMut);
		thisPlayer->playCond.wait(playLock, [thisPlayer] { return thisPlayer->playerState == PLAYING; });
		WaveFileBlock wfb = thisPlayer->bufferQueue.front();
		waveOutUnprepareHeader(thisPlayer->hWaveOut, &wfb.header, sizeof(WAVEHDR));
		cout << "hi\n";
		playLock.unlock();
		thisPlayer->playCond.notify_all();
		//unique_lock<mutex> bufLock(thisPlayer->bufferMut);
		//thisPlayer->bufCond.wait(bufLock, [thisPlayer] { return thisPlayer->bufferQueue.size() > 0; });
		thisPlayer->bufferQueue.pop();
		cout << "Pop front buffer\n";*/
		//bufLock.unlock();
		/*thisPlayer->playMut.unlock();
		if (!thisPlayer->bufferQueue.empty()) {
			while (true) {
				if (thisPlayer->bufferMut.try_lock()) {
					cout << "buffer locked" << endl;
					thisPlayer->bufferQueue.pop();
					cout << "pop buffer queue" << endl;
					thisPlayer->bufferMut.unlock();
					cout << "buffer unlocked" << endl;
					break;
				}
			}
		}*/
		break;
	}
	case WOM_OPEN: {
		cout << "OPENED" << endl;
		break;
	}
	case WOM_CLOSE: {
		cout << "CLOSED" << endl;
		break;
	}
	}
}