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
	 * @brief ��ʼ����Ϸ
	 */
	virtual ~Game() = default;

	/**
	 * @brief ��Ҽ�����Ϸ
	 * @param participant ������QQ��
	 */
	virtual ParticipateState Join(elong participant) = 0;

	/**
	 * @brief ����˳���Ϸ
	 * @param participant �˳���QQ��
	 */
	virtual QuitState Quit(elong participant) = 0;

	/**
	 * @brief ������Ϸ
	 */
	virtual bool Cancel() = 0;

	/**
	 * @brief ��ʼ��Ϸ
	 */
	virtual bool Start() = 0;
};