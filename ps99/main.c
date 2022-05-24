#include <stdio.h>
#include "track.h"
#include "playlist.h"

int main(){
	struct track* track = create_track("Wait", 355);
	free_track(track);
	struct playlist* playlist = create_playlist("M83");
	append_track_to_playlist(playlist, create_track("Wait", 355));
	append_track_to_playlist(playlist, create_track("Outro", 247));
	play(playlist);
	change_mode(playlist, DONT_REPEAT);
	next(playlist);
	prev(playlist);
	free_playlist(playlist);
	return 0;
}
