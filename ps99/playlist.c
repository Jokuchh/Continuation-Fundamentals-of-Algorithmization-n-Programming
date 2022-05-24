#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"


struct playlist* create_playlist(char* name){
	if (strlen(name) == 0) return NULL;
    if (strlen(name) > 100) return NULL;
	struct playlist* playlist_temp = (struct playlist*)malloc(sizeof(struct playlist));
	playlist_temp->name = (char*)malloc((strlen(name)) * sizeof(char) + 1);
	strcpy(playlist_temp->name, name);
	playlist_temp->mode = REPEAT;
	playlist_temp->size = 0;
	playlist_temp->duration = 0;
	playlist_temp->first = NULL;
	playlist_temp->current = NULL;
	return playlist_temp;
}

void append_track_to_playlist(struct playlist *playlist, struct track *track){
	if (!playlist) return;
	if (!track) return;
	if(!playlist->first){
		playlist->first = (struct entry*)malloc(sizeof(struct entry));
		playlist->first->track = track;
		playlist->first->prev = NULL;
		playlist->first->next = NULL;
		playlist->current = (struct entry*)malloc(sizeof(struct entry));
		playlist->current->track = track;
		playlist->current->prev = NULL;
        playlist->current->next = NULL;
	} else {
		struct entry* entry_temp = playlist->first;
		struct entry* next_entry = (struct entry*)malloc(sizeof(struct entry));
		while(entry_temp->next){
			entry_temp = entry_temp->next;
		}
		next_entry->next = NULL;
		next_entry->prev = entry_temp;
		next_entry->track = track;
		entry_temp->next = next_entry;
	}
	playlist->size = playlist->size + 1;
	playlist->duration = playlist->duration + track->duration;
}


struct track* play(struct playlist* playlist){
	if(!playlist) return NULL;
	if(!playlist->current->track) return NULL;
	struct track* temp_track = playlist->current->track;
	printf("Now song is: %s\n", playlist->current->track->title);
	struct entry* entry_temp = playlist->first;
	while (entry_temp->next) {
			if (strcmp(playlist->current->track->title, entry_temp->track->title) == 0) {
				playlist->current = entry_temp;
				break;
			}
            entry_temp = entry_temp->next;
	}
	if(playlist->mode == DONT_REPEAT){
		if(playlist->current->next)
        	playlist->current = playlist->current->next;
        else return temp_track;
	}
	if(playlist->mode == REPEAT){
		if(playlist->current->next)
			playlist->current = playlist->current->next;
		else playlist->current = playlist->first;
	}
	return temp_track;
}


struct track* next(struct playlist* playlist){
	if(!playlist->current->track) return NULL;
	if(!playlist) return NULL;
    struct entry* nextt = playlist->first;
    while(nextt->next){
	    if(strcmp(playlist->current->track->title, nextt->track->title) == 0){
	            playlist->current = nextt;
	            break;
	    }
	    nextt = nextt->next;
    }
	if(playlist->current->next){
		playlist->current = nextt->next;
		return playlist->current->track;
	}
	else return playlist->current->track;
}


struct track* prev(struct playlist* playlist){
	if(!playlist->current->track) return NULL;
	if(!playlist) return NULL;
    struct entry* previous = playlist->first;
    while(previous->next){
	    if(strcmp(playlist->current->track->title, previous->track->title) == 0){
	            playlist->current = previous;
	            break;
	    }
	    previous = previous->next;
    }
	if(playlist->current->prev){
		playlist->current = previous->prev;
		return playlist->current->track;
	}
	else return playlist->current->track;
}


void change_mode(struct playlist* playlist, enum play_mode mode) {
	if (playlist) {
		playlist->mode = mode;
	} else return;
}


void free_playlist(struct playlist* playlist){
	free(playlist->name);
    free(playlist);
}



