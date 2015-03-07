#include "PrimThread.hpp"

// PrimThread
PrimThread::PrimThread() : last(0) {}
PrimThread::~PrimThread(){}

bool PrimThread::operator<(const PrimThread& rhs) const {
	return this->last < rhs.last;
}

void PrimThread::append_msg(struct SMessage *m){
	last = (m->Date > last) ? m->Date : last;
	M.push_back(*m);
}

// ThreadAcc
ThreadAcc::ThreadAcc(){}
ThreadAcc::~ThreadAcc(){}

// TODO optimize for topics
bool ThreadAcc::consume(SMessage *messages, int size){

	PrimThread pt;
	for(int i = 0; i < size; i++){
		// return false if there's no need to print at all
		if (messages[i].Date < current_minprntime && currentlsel == 1)
			return false;
		if(!messages[i].Level) T.push_back(pt);
		T.end()->append_msg(&messages[i]);
	}
	return true;
}

void ThreadAcc::sort(){
	std::sort(T.begin(), T.end());
}
