// 包含 CornerstoneSDK
#include "sdk/sdk.h"

#include <cstdint>
#include <string>
#include <ctime>

using namespace std;

// Cornerstone SDK 可能存在漏洞
// 欢迎前往 https://github.com/Sc-Softs/CornerstoneSDK 提交Issue和PR，感谢您的贡献

// 插件信息 请注意最后一行末尾是不能有多余逗号
const char *Configuration = R"CFG(
{
	"插件名称": "Shrimp QQ AI插件",
	"插件作者": "AlerHuGhe$",
	"插件版本": "1.0.0",
	"插件说明": "爱咋咋地",
	"所需权限":
	{
		"输出日志": "<这里填写申请理由>",
		"发送好友消息": "与好友互动",
		"发送群消息": "与群成员互动",
		"发送群临时消息": "与群成员单独互动",
		"取好友列表": "测试用",
		"取群列表": "测试用",
		"取群成员列表": "测试用"
	}
}
)CFG";

const char* szName[22] =
{
	"愚者",
	"魔法师",
	"女祭司",
	"女皇",
	"皇帝",
	"法皇",
	"恋人",
	"战车",
	"力量",
	"隐者",
	"命运之轮",
	"正义",
	"倒吊者",
	"死神",
	"节制",
	"恶魔",
	"塔",
	"星星",
	"月",
	"太阳",
	"审判",
	"世界"
};

const char* szDesc[44] =
{
	"无忧无虑、轻松愉快。古怪、与众不同。不成熟。出乎意料的。",
	"奇特的习惯。精神错乱，胡言乱语。疯狂、发怒。狂喜、醉。",
	"自愿、乐意。自治、独立。技术、熟练。精明、灵敏。外交、交际。",
	"说谎。攀权附贵。诡计、谋略、耍花招。",
	"学习、研究。直觉。秘密。信念、信赖。神秘。",
	"无知。偏见。歇斯底里。",
	"肥沃、多产。理解。交换意见。帮助、分享。怀孕。",
	"愚蠢。不孕。轻薄、无趣。",
	"稳定、安定。力量。权力。守护、保卫。",
	"注视着伟大的事物。傲慢、自大。敌对、反抗。",
	"灵感。慈悲、仁爱。慰藉、援助、解救。有耐心。依循传统。",
	"仇恨、憎恨。无法宽容。不道德、邪恶。",
	"选择。企图、尝试。检查、调查。缔结，婚约、订约。合并、结合、合而为一。",
	"不守誓约、通奸、外遇。分离。优柔寡断。",
	"胜利。经营的技能。公众人物、大众认可。",
	"失败。无能。失误。",
	"活力、能量。道德勇气。棘手的工作、强健的工作。勇敢。",
	"怠惰、懒散。冲动。虚弱、软弱。",
	"谨慎、慎重。沉思、冥想。孤独、隐居。寂静、无声。",
	"顾影自怜。妒忌。拖延，延迟，耽搁。",
	"轮流、交替。大自然的循环。改变。好机会。",
	"不稳定。失去优势。",
	"冷静、明智。法律。逻辑、有道理的。划分阶级。",
	"不公平、失去正义。法律问题。混乱、没有秩序。",
	"牺牲、奉献。理想化、理想主义。有利他人的行为、利他主义。对神秘事物的狂热份子",
	"无能。生病。",
	"结束。突然的且激烈的改变。开始。",
	"危险的阻碍，令人担心的难关。逆境。",
	"温和、适度。适应、通融。足够的休息、有益健康的休养。关心。",
	"焦虑、挂念。不舒服、不愿意。",
	"本能、天性。魅力、吸引力。感官享受、好色。暗示。",
	"堕落，曲解。不安、烦乱。憎恨、讨厌。",
	"逃避、避免。仓促的起程。流放、流亡。粉碎必然的事物、打破习惯传统。危险。",
	"事故、灾难。毁灭。混乱。",
	"希望。明显的指引。新的想法。和平、和睦。",
	"不幸的征召。辞职，放弃。",
	"梦。幻觉。冒险。不可思议的遭遇。旅行。",
	"危险。邪恶。谎言。",
	"同意、一致。友善、友谊。爱。荣誉。欢乐。",
	"痛苦、不幸。利己主义、自我中心。易怒。",
	"复活、回复、更新。生日，出生。觉醒。重新获得、恢复。",
	"怀疑、不相信。悔恨、懊悔、遗憾。生病。",
	"报答、奖赏、结果。完美。成功。继承、遗传、传统。时间、一段时光。",
	"延期、拖延。迷惑、欺骗。失败。"
};

// 事件处理函数 请勿在函数中执行上传文件等耗时操作，此类操作请另开线程执行

// 私聊消息事件
EventProcessEnum OnPrivateMessage(PrivateMessageData data)
{
	return EventProcessEnum::Ignore;
/*
	// 判断是否是长消息自动分片的片段内容（序列从0开始）
	if (data.MessageClipID > 0 && data.MessageClip + 1 != data.MessageClipCount)
	{
		// 不处理长消息自动分片的片段内容
		return EventProcessEnum::Ignore;
	}

	// 判断是否是自己发送的消息
	if (data.ThisQQ == data.SenderQQ)
	{
		// 不处理自己发送的消息
		return EventProcessEnum::Ignore;
	}

	// 判断消息类型，只处理群临时消息和好友普通消息
	if (data.MessageType == MessageTypeEnum::FriendUsualMessage)
	{
		// 判断是否为普通消息，需要检查红包类型是否等于0
		if (data.RedEnvelopeType != 0)
		{
			// 不处理其他消息
			return EventProcessEnum::Ignore;
		}
	}
	else if (data.MessageType == MessageTypeEnum::Temporary)
	{
		// 判断是否为群临时消息
		if (data.MessageSubTemporaryType != MessageSubTypeEnum::Temporary_Group)
		{
			// 不处理其他消息
			return EventProcessEnum::Ignore;
		}
	}
	else
	{
		// 不处理其他消息
		return EventProcessEnum::Ignore;
	}

	std::string content = data.MessageContent;
	std::string ret;
	// 判断消息内容
	if (content == "CornerstoneSDK测试")
	{
		api->OutputLog("好友消息测试");
		ret = "好友消息测试";
	}
	else if (content == "CornerstoneSDK测试获取好友列表")
	{
		vector<FriendInformation> friend_list;
		// 获取好友列表
		auto size = api->GetFriendList(data.ThisQQ, friend_list);
		// 判断是否获取成功
		if (size == 0)
		{
			api->OutputLog("好友列表获取失败: 返回的size为0");
			ret = "好友列表获取失败: 返回的size为0";
		}
		else
		{
			api->OutputLog(sum_string("好友列表获取成功: 返回的size为", size));
			string friends;
			for (auto friend_info : friend_list)
			{
				friends += sum_string(friend_info.QQNumber, ": ", friend_info.Name, "\n");
			}
			ret = friends;
		}
	}
	else if (content == "CornerstoneSDK测试获取群列表")
	{
		vector<GroupInformation> group_list;
		// 获取群列表
		auto size = api->GetGroupList(data.ThisQQ, group_list);
		// 判断是否获取成功
		if (size == 0)
		{
			api->OutputLog("群列表获取失败: 返回的size为0");
			ret = "群列表获取失败: 返回的size为0";
		}
		else
		{
			api->OutputLog(sum_string("群列表获取成功: 返回的size为", size));
			string groups;
			for (auto group_info : group_list)
			{
				groups += sum_string(group_info.GroupQQ, ": ", group_info.GroupName, "\n");
			}
			ret = groups;
		}
	}
	else if (content == "今日运势")
	{
		srand((int)time(NULL));
		int luck = (rand() + data.MessageSendTime) % 100;
		if (luck <= 5)
		{
			ret = "咚咚哒 "+ data.SourceEventQQName +"的今日运势为:" + to_string(luck) + " 哈哈哈哈哈哈哈";
		}
		else if (luck <= 50)
		{
			ret = data.SourceEventQQName + "的今日运势为:" + to_string(luck) + " 你今天有一丶倒霉";
		}
		else if (luck < 95)
		{
			ret = data.SourceEventQQName + "的今日运势为:" + to_string(luck) + " 你还是人吗？";
		}
		else
		{
			ret = "啊这 啊这 "+data.SourceEventQQName + "的今日运势为:" + to_string(luck) + " 🐂🍺嗷";
		}
	}

	// 判断有没有要回复的消息
	if (ret.empty())
	{
		return EventProcessEnum::Ignore;
	}

	// 根据不同的消息来源调用不同的发送信息函数
	if (data.MessageType == MessageTypeEnum::FriendUsualMessage)
	{
		api->SendFriendMessage(data.ThisQQ, data.SenderQQ, ret);
	}
	else if (data.MessageType == MessageTypeEnum::Temporary)
	{
		api->SendGroupTemporaryMessage(data.ThisQQ, data.MessageGroupQQ, data.SenderQQ, ret);
	}

	// 已经处理过的消息返回Block阻止其他插件继续处理
	return EventProcessEnum::Ignore;
*/
}

// 群消息事件
EventProcessEnum OnGroupMessage(GroupMessageData data)
{
	// 判断是否是长消息自动分片的片段内容（序列从0开始）
	if (data.MessageClipID > 0 && data.MessageClip + 1 != data.MessageClipCount)
	{
		// 不处理长消息自动分片的片段内容
		return EventProcessEnum::Ignore;
	}

	// 判断是否是自己发送的消息
	if (data.ThisQQ == data.SenderQQ)
	{
		// 不处理自己发送的消息
		return EventProcessEnum::Ignore;
	}

	api->OutputLog(sum_string("群聊消息: ", (eint)data.MessageType));
	// 判断消息类型，只处理普通群聊信息
	if ((eint)data.MessageType != 82)
	{
		// 不处理其他消息
		return EventProcessEnum::Ignore;
	}

	std::string content = data.MessageContent;
	// 判断消息内容
	/*
	if (content == "CornerstoneSDK测试")
	{
		api->OutputLog("群消息测试");
		api->SendGroupMessage(data.ThisQQ, data.MessageGroupQQ, "群消息测试");
		auto retcode = get_retcode(api->SendGroupTemporaryMessage(data.ThisQQ, data.MessageGroupQQ, data.SenderQQ, "临时消息测试"));
		if (retcode != 0)
		{
			api->OutputLog(sum_string("临时消息发送失败: ", retcode));
		}
	}
	else if (content == "CornerstoneSDK测试获取群成员列表")
	{
		vector<GroupMemberInformation> member_list;
		// 获取群成员列表
		auto size = api->GetGroupMemberList(data.ThisQQ, data.MessageGroupQQ, member_list);
		// 判断是否获取成功
		if (size == 0)
		{
			api->OutputLog("群成员列表获取失败: 返回的size为0");
			api->SendGroupMessage(data.ThisQQ, data.MessageGroupQQ, "群成员列表获取失败: 返回的size为0");
		}
		else
		{
			api->OutputLog(sum_string("群成员列表获取成功: 返回的size为", size));
			string members;
			// 最多只显示5个群成员
			if (size > 5)
				size = 5;
			for (decltype(size) i = 0; i < size; i++)
			{
				auto member_info = member_list[i];
				members += sum_string(member_info.QQNumber, ": ", member_info.Name, "\n");
			}
			api->SendGroupMessage(data.ThisQQ, data.MessageGroupQQ, members);
		}
	}
	*/
	if (content == "今日运势")
	{
		api->OutputLog("捕获到今日运势查询");
		// 根据QQ号、群号、日期，产生随机数
		time_t tt = time(NULL);
		tm* t = localtime(&tt);
		int seed = t->tm_mday * 88 + (data.SenderQQ / 1000 + data.SenderQQ % 10000) % 888 + data.MessageGroupQQ % 100 + t->tm_yday * 12 + t->tm_wday * 998;
		srand(seed);
		int luck = rand() % 101;

		string ret;
		if (luck <= 5)
		{
			ret = "咚咚哒 [@" + to_string(data.SenderQQ) + "] 的今日运势为:" + to_string(luck) + " 哈哈哈哈哈哈哈";
		}
		else if (luck <= 50)
		{
			ret = "[@" + to_string(data.SenderQQ) + "] 的今日运势为:" + to_string(luck) + " 你今天有一丶倒霉";
		}
		else if (luck < 95)
		{
			ret = "[@" + to_string(data.SenderQQ) + "] 的今日运势为:" + to_string(luck) + " 你还是人吗？";
		}
		else
		{
			ret = "啊这 啊这 [@" + to_string(data.SenderQQ) + "] 的今日运势为:" + to_string(luck) + " 🐂🍺嗷";
		}
		api->SendGroupMessage(data.ThisQQ, data.MessageGroupQQ, ret);
	}
	else if (content.length() > 5 && content.substr(0, 6) == "占卜")
	{
		api->OutputLog("捕获到占卜查询");
		string text = "";
		if (content.length() > 6)
			text = content.substr(6, content.length());
			
		// 根据时间、QQ号、群号产生随机数
		srand((int)(time(0) + data.SenderQQ % 10 + data.MessageGroupQQ % 100));
		int result = rand() % 22;
		if (rand() % 2)
			text = "[@" + to_string(data.SenderQQ) + "] 占卜 " + text + " \n" + szName[result] + " 正位：" + szDesc[result * 2];
		else
			text = "[@" + to_string(data.SenderQQ) + "] 占卜 " + text + " \n" + szName[result] + " 逆位：" + szDesc[result * 2 + 1];

		api->SendGroupMessage(data.ThisQQ, data.MessageGroupQQ, text);
	}
	else
	{
		// 未处理过的消息
		return EventProcessEnum::Ignore;
	}

	// 已经处理过的消息阻止其他插件继续处理
	return EventProcessEnum::Ignore;
}

// 插件卸载事件
EventProcessEnum OnUninstall()
{
	return EventProcessEnum::Ignore;
}

// 插件设置事件 这里可以弹出对话框
EventProcessEnum OnSettings()
{
	return EventProcessEnum::Ignore;
}

// 插件被启用事件
EventProcessEnum OnEnabled()
{
	return EventProcessEnum::Ignore;
}

// 插件被禁用事件
EventProcessEnum OnDisabled()
{
	return EventProcessEnum::Ignore;
}

// 其他事件
EventProcessEnum OnEvent(EventData data)
{
	// 判断是否是群事件
	if (data.SourceGroupQQ == 0)
	{
		// 非群事件
		switch (data.EventType)
		{
		// 好友事件_被好友删除
		case EventTypeEnum::Friend_Removed:
			break;
		// 好友事件_签名变更
		case EventTypeEnum::Friend_SignatureChanged:
			break;
		// 好友事件_昵称改变
		case EventTypeEnum::Friend_NameChanged:
			break;
		// 好友事件_某人撤回事件
		case EventTypeEnum::Friend_UserUndid:
			break;
		// 好友事件_有新好友
		case EventTypeEnum::Friend_NewFriend:
			break;
		// 好友事件_好友请求
		case EventTypeEnum::Friend_FriendRequest:
			break;
		// 好友事件_对方同意了您的好友请求
		case EventTypeEnum::Friend_FriendRequestAccepted:
			break;
		// 好友事件_对方拒绝了您的好友请求
		case EventTypeEnum::Friend_FriendRequestRefused:
			break;
		// 好友事件_资料卡点赞
		case EventTypeEnum::Friend_InformationLiked:
			break;
		// 好友事件_签名点赞
		case EventTypeEnum::Friend_SignatureLiked:
			break;
		// 好友事件_签名回复
		case EventTypeEnum::Friend_SignatureReplied:
			break;
		// 好友事件_个性标签点赞
		case EventTypeEnum::Friend_TagLiked:
			break;
		// 好友事件_随心贴回复
		case EventTypeEnum::Friend_StickerLiked:
			break;
		// 好友事件_随心贴增添
		case EventTypeEnum::Friend_StickerAdded:
			break;
		// 空间事件_与我相关
		case EventTypeEnum::QZone_Related:
			break;
		// 框架事件_登录成功
		case EventTypeEnum::This_SignInSuccess:
			break;
		// 其他事件
		default:
			break;
		}
	}
	else
	{
		// 群事件
		switch (data.EventType)
		{
		// 群事件_我被邀请加入群
		case EventTypeEnum::Group_Invited:
			break;
		// 群事件_某人加入了群
		case EventTypeEnum::Group_MemberJoined:
			break;
		// 群事件_某人申请加群
		case EventTypeEnum::Group_MemberVerifying:
			break;
		// 群事件_群被解散
		case EventTypeEnum::Group_GroupDissolved:
			break;
		// 群事件_某人退出了群
		case EventTypeEnum::Group_MemberQuit:
			break;
		// 群事件_某人被踢出群
		case EventTypeEnum::Group_MemberKicked:
			break;
		// 群事件_某人被禁言
		case EventTypeEnum::Group_MemberShutUp:
			break;
		// 群事件_某人撤回事件
		case EventTypeEnum::Group_MemberUndid:
			break;
		// 群事件_某人被取消管理
		case EventTypeEnum::Group_AdministratorTook:
			break;
		// 群事件_某人被赋予管理
		case EventTypeEnum::Group_AdministratorGave:
			break;
		// 群事件_开启全员禁言
		case EventTypeEnum::Group_EnableAllShutUp:
			break;
		// 群事件_关闭全员禁言
		case EventTypeEnum::Group_DisableAllShutUp:
			break;
		// 群事件_开启匿名聊天
		case EventTypeEnum::Group_EnableAnonymous:
			break;
		// 群事件_关闭匿名聊天
		case EventTypeEnum::Group_DisableAnonymous:
			break;
		// 群事件_开启坦白说
		case EventTypeEnum::Group_EnableChatFrankly:
			break;
		// 群事件_关闭坦白说
		case EventTypeEnum::Group_DisableChatFrankly:
			break;
		// 群事件_允许群临时会话
		case EventTypeEnum::Group_AllowGroupTemporary:
			break;
		// 群事件_禁止群临时会话
		case EventTypeEnum::Group_ForbidGroupTemporary:
			break;
		// 群事件_允许发起新的群聊
		case EventTypeEnum::Group_AllowCreateGroup:
			break;
		// 群事件_禁止发起新的群聊
		case EventTypeEnum::Group_ForbidCreateGroup:
			break;
		// 群事件_允许上传群文件
		case EventTypeEnum::Group_AllowUploadFile:
			break;
		// 群事件_禁止上传群文件
		case EventTypeEnum::Group_ForbidUploadFile:
			break;
		// 群事件_允许上传相册
		case EventTypeEnum::Group_AllowUploadPicture:
			break;
		// 群事件_禁止上传相册
		case EventTypeEnum::Group_ForbidUploadPicture:
			break;
		// 群事件_某人被邀请入群
		case EventTypeEnum::Group_MemberInvited:
			break;
		// 群事件_展示成员群头衔
		case EventTypeEnum::Group_ShowMemberTitle:
			break;
		// 群事件_隐藏成员群头衔
		case EventTypeEnum::Group_HideMemberTitle:
			break;
		// 群事件_某人被解除禁言
		case EventTypeEnum::Group_MemberNotShutUp:
			break;
		// 其他事件
		default:
			break;
		}
	}
	return EventProcessEnum::Ignore;
}
