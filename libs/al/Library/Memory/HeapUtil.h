#pragma once

#include <heap/seadHeap.h>

namespace al {

class AudioResourceDirector;

sead::Heap* getStationedHeap();
sead::Heap* getCurrentHeap();

sead::Heap* getSceneResourceHeap(void);
sead::Heap* getSceneHeap(void);
sead::Heap* getSequenceHeap(void);
sead::Heap* getCourseSelectResourceHeap(void);
sead::Heap* getCourseSelectHeap(void);
sead::Heap* getWorldResourceHeap(void);
sead::Heap* tryFindNamedHeap(char const*);
sead::Heap* findNamedHeap(char const*);
void addNamedHeap(sead::Heap *,char const*);
void removeNamedHeap(char const*);
void createSequenceHeap(void);
void freeAllSequenceHeap(void);
void printAllSequenceHeap(void);
void createSceneHeap(char const*,bool);
void createSceneResourceHeap(char const*);
void isCreatedSceneResourceHeap(void);
void destroySceneHeap(bool);
void createCourseSelectHeap(void);
void destroyCourseSelectHeap(void);
void createWorldResourceHeap(bool);
void destroyWorldResourceHeap(bool);
void loadPlayerResource(char const*);
void freePlayerResource(char const*);
void setAudioResourceDirectorToMemorySystem(al::AudioResourceDirector *);
}
