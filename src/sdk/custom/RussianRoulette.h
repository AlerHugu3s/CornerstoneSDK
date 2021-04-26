#pragma once
#include <vector>
#include "Game.h"

class RussianRoulette : public Game
{

public:
	enum class ShotState
	{
		empty,notParticipant,getShot,notGetShot
	};
	/**
	 * @brief ����˹ת�̳�ʼ��
	 */
	RussianRoulette();

	/**
	 * @brief �������ؼ��ֺ�ϵͳAPI����ָ��
	 * @param api_data ϵͳAPI����ָ��JSON
	 * @param plugin_key �����ʶ��
	 */
	~RussianRoulette() = default;

	/**
	 * @brief �������ؼ��ֺ�ϵͳAPI����ָ��
	 * @param api_data ϵͳAPI����ָ��JSON
	 * @param plugin_key �����ʶ��
	 */
	ParticipateState Join(elong participant) override;

	/**
	 * @brief �������ؼ��ֺ�ϵͳAPI����ָ��
	 * @param api_data ϵͳAPI����ָ��JSON
	 * @param plugin_key �����ʶ��
	 */
	QuitState Quit(elong participant) override;

	/**
	 * @brief �������ؼ��ֺ�ϵͳAPI����ָ��
	 * @param api_data ϵͳAPI����ָ��JSON
	 * @param plugin_key �����ʶ��
	 */
	bool Cancel() override;

	/**
	 * @brief �������ؼ��ֺ�ϵͳAPI����ָ��
	 * @param api_data ϵͳAPI����ָ��JSON
	 * @param plugin_key �����ʶ��
	 */
	bool Start() override;

	bool SetGameInfo(int maxPlayer, int maxSpace,int bullets);

	ShotState Shot(elong participant);

	static RussianRoulette* GetInstance() { return s_Instance; }
private:
	std::vector<elong> m_Participants;
	std::vector<int> m_Roulette;
	int m_maxPlayer;
	GameState m_GameState;

	static RussianRoulette* s_Instance;
};