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
	 * @brief 俄罗斯转盘初始化
	 */
	RussianRoulette();

	/**
	 * @brief 载入插件关键字和系统API函数指针
	 * @param api_data 系统API函数指针JSON
	 * @param plugin_key 插件标识符
	 */
	~RussianRoulette() = default;

	/**
	 * @brief 载入插件关键字和系统API函数指针
	 * @param api_data 系统API函数指针JSON
	 * @param plugin_key 插件标识符
	 */
	ParticipateState Join(elong participant) override;

	/**
	 * @brief 载入插件关键字和系统API函数指针
	 * @param api_data 系统API函数指针JSON
	 * @param plugin_key 插件标识符
	 */
	QuitState Quit(elong participant) override;

	/**
	 * @brief 载入插件关键字和系统API函数指针
	 * @param api_data 系统API函数指针JSON
	 * @param plugin_key 插件标识符
	 */
	bool Cancel() override;

	/**
	 * @brief 载入插件关键字和系统API函数指针
	 * @param api_data 系统API函数指针JSON
	 * @param plugin_key 插件标识符
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