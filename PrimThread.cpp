// BUMP, requested by Demon:
// http://zlo.rt.mipt.ru/?read=8823385
// implemented by Judge_Dredd, config option proposed by Selenka

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
ThreadAcc::ThreadAcc() : consumed(0) {}
ThreadAcc::~ThreadAcc(){}

// TODO optimize for topics
bool ThreadAcc::consume(SMessage *messages, int size, bool d){

	PrimThread pt;
	for(int i = d ? 0 : size/sizeof(SMessage) - 1;
	    d ? (unsigned) i < size/sizeof(SMessage) : i >= 0;
	    d ? i++ : i--){
		// return false if there's no need to print at all
		// need to check here because print won't be able
		// to check for us anymore (not called until
		// everythin' is sorted) (cope-paste from dbase.cpp)
		if((messages[i].Date < current_minprntime && currentlsel == 1)
		   || (currentlsel == 2 && this->consumed == currenttc))
			return false;

		if(!messages[i].Level){
			T.push_back(pt);
			++this->consumed;
		}

		T.rbegin()->append_msg(&messages[i]);
	}
	return true;
}

void ThreadAcc::sort(){
	std::sort(T.begin(), T.end());
}
