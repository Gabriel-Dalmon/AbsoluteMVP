#include "pch.h"

void ThreadApp::OnThread(HINSTANCE hInstance)
{
	m_pFactory = new GameFactory();
	m_pEngine = new SleepyEngine(hInstance);

	m_pEngine->SetFactory(m_pFactory);
	m_pEngine->Initialize();
	m_pEngine->Run();
}

void ThreadApp::Release()
{
	RELEASE(m_pEngine);
	RELEASE(m_pFactory);
	DELETE(m_pEngine);
	DELETE(m_pFactory);
}
