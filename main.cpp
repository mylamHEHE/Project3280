#include <stdio.h>
#include <iostream>
#include "MusicPlayer.h"

int main() {
	MusicPlayer mp;
	mp.OpenFile("test.wav");
	mp.SetVolume(0xffff, 0xffff);
	mp.Playback(0);
	cout << "finish playback\n";
	mp.ClosePlayer();
	getchar();
	return 0;
}