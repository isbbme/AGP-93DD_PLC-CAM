#pragma once
#include "Infra/Thread.h"
#include "GenICam/StreamSource.h"

using namespace Dahua::GenICam;
using namespace Dahua::Infra;


class StreamRetrieve : public CThread
{
public:
	StreamRetrieve(IStreamSourcePtr& streamSptr);
	bool start(DWORD c, DWORD vx, DWORD vz, DWORD vz1, DWORD vpltz);


	void stop();
private:
	void threadProc();
	bool m_isLoop;
	IStreamSourcePtr m_streamSptr;
	DWORD coordinatee, coordinatee1, coordinatee2, coordinatee3, coordinatee4;

};