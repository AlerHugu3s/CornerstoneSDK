#pragma once
#include "../utils/types.h"

class Game
{
public:
	enum class GameState
	{
		ready, playing, sleep
	};
	enum class ParticipateState
	{
		alreadyParticipate, success, full
	};
	enum class QuitState
	{
		notParticipate, success
	};

	/**
	 * @brief 初始化游戏
	 */
	virtual ~Game() = default;

	/**
	 * @brief 玩家加入游戏
	 * @param participant 参与者QQ号
	 */
	virtual ParticipateState Join(elong participant) = 0;

	/**
	 * @brief 玩家退出游戏
	 * @param participant 退出者QQ号
	 */
	virtual QuitState Quit(elong participant) = 0;

	/**
	 * @brief 结束游戏
	 */
	virtual bool Cancel() = 0;

	/**
	 * @brief 开始游戏
	 */
	virtual bool Start() = 0;
};