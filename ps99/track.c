#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "track.h"


struct track* create_track(const char* title, int duration){
	if(strlen(title) > 100)	return NULL;
	if(strlen(title) == 0)	return NULL;
	if(duration <= 0) return NULL;
	struct track* track = (struct track*)malloc(sizeof(struct track));
	track->title =  (char*)malloc((strlen(title) + 1) * sizeof(char));
	strcpy(track->title, title);
	track->duration = duration;
	return track;
}


void free_track(struct track* track){
	free(track);
}


