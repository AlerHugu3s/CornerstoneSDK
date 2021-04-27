#include "RussianRoulette.h"

#include <algorithm>
#include <random>

RussianRoulette* RussianRoulette::s_Instance = new RussianRoulette();

RussianRoulette::RussianRoulette()
	: m_GameState(GameState::sleep)
{
	s_Instance = this;
	m_maxPlayer = 0;
	m_GameState = Game::GameState::sleep;
}

Game::ParticipateState RussianRoulette::Join(elong participant)
{
	if (m_Participants.size() >= m_maxPlayer) return Game::ParticipateState::full;
	if (std::find(m_Participants.begin(), m_Participants.end(), participant) != m_Participants.end()) return Game::ParticipateState::alreadyParticipate;

	m_Participants.push_back(participant);

	if (m_Participants.size() > 0) m_GameState = GameState::ready;
	return Game::ParticipateState::success;
}

Game::QuitState RussianRoulette::Quit(elong participant)
{
	std::vector<elong>::iterator index = std::find(m_Participants.begin(), m_Participants.end(), participant);
	if (index == m_Participants.end()) return Game::QuitState::notParticipate;

	m_Participants.erase(index);
	if (m_Participants.size() == 0) m_GameState = GameState::sleep;
	return Game::QuitState::success;
}

bool RussianRoulette::Cancel()
{
	m_Participants.clear();
	m_Roulette.clear();
	m_GameState = Game::GameState::sleep;
	return false;
}

bool RussianRoulette::Start()
{
	if (m_GameState == GameState::ready)
	{
		m_GameState = GameState::playing;
		return true;
	}
	return false;
}

bool RussianRoulette::SetGameInfo(int maxPlayer,int maxSpace, int bullets)
{
	if (m_GameState == GameState::sleep && bullets < maxSpace && maxPlayer > 0 && maxSpace > 0 && bullets > 0)
	{
		m_maxPlayer = maxPlayer;
		for (int i = 0; i < bullets; i++)
		{
			m_Roulette.push_back(1);
		}
		for (int i = 0; i < maxSpace - bullets; i++)
		{
			m_Roulette.push_back(0);
		}
		
		std::random_device rd;
		std::shuffle(m_Roulette.begin(), m_Roulette.end(), std::default_random_engine(rd()));
		return true;
	}
	return false;
}

RussianRoulette::ShotState RussianRoulette::Shot(elong participant)
{
	if (m_GameState == GameState::playing)
	{
		if (m_Roulette.empty())
		{
			Cancel();
			return ShotState::empty;
		}

		if (std::find(m_Participants.begin(), m_Participants.end(), participant) != m_Participants.end())
		{
			int result = m_Roulette.back();
			m_Roulette.pop_back();
			if (result == 0) return ShotState::notGetShot;
			else return ShotState::getShot;
		}

	}
	return ShotState::notParticipant;
}
