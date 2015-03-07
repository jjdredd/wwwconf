#ifndef PRIM_THREAD
#define PRIM_THREAD

#include <vector>
#include <algorithm>
#include "basetypes.h"
#include "dbase.h"

/* a very primitive thread structure for sorting */
class PrimThread {

	friend class DB_Base;

public:
	PrimThread();
	~PrimThread();
	bool operator<(const PrimThread& rhs) const;
	void append_msg(struct SMessage *m);

private:
	time_t last;
	std::vector<struct SMessage> M;
};

class ThreadAcc {

	friend class DB_Base;

public:
	ThreadAcc();
	~ThreadAcc();
	bool consume(struct SMessage *messages, int size);
	void sort();

private:
	unsigned consumed;
	std::vector<PrimThread> T;
};

#endif	// PRIM_THREAD
