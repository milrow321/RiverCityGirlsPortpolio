#pragma once
#include "ProgressBar.h"
#include "Player.h"

#define PLAYERHPMAX 23
#define SHOPLISTMAX 4

struct tagPlayerInfo
{	
	Image*	frameHp;	// 체력 프레임
	Image*	hpDigit;	// 체력 한칸 이미지
	float	currentHp;	// 현재 체력
	float	maxHp;		// 최대 체력	
	Vector2 pos;		// 좌표
	bool	active;		// 출력 및 업데이트 여부
	int		digitNum;	// 체력 칸 개수

	float	money;

	// 경험치 관련
	ProgressBar* expBar;		// 경험치 막대
	float		 currentExp;	// 현재 경험치
	float		 maxExp;		// 최대 경험치


	HRESULT init()
	{
		frameHp = IMAGE_MANAGER->findImage("playerHpFrame");
		hpDigit = IMAGE_MANAGER->findImage("playerDigit");
		digitNum = PLAYERHPMAX;
		expBar = new ProgressBar;
		expBar->init("playerExpBack", "playerExpFront", Vector2(WINSIZEX / 2 - 288.0f, 61.3f), Vector2(-30.0f, 0.0f), 0.7f);

		return S_OK;
	}
	void update(class Player* player)
	{
		if (active)
		{
			digitNum = (int)(((float) player->getHp() / player->getMaxHp()) * PLAYERHPMAX);	// 체력바 갯수 설정

			// 체력바는 0개인데 체력은 아직 남아있는 경우
			if (!digitNum && player->getHp() > 0)
			{
				digitNum = 1;	// 체력바는 1로 만들어줌
			}
			expBar->update();
			expBar->setGauge((float)player->getExp(), 100.0f);

			money = (float)player->getMoney();			
		}
	}
	void render()
	{
		if (active)
		{
			IMAGE_MANAGER->findImage("playerBackBar")->setAlpha(0.8f);
			IMAGE_MANAGER->findImage("playerBackBar")->setScale(0.7f);
			IMAGE_MANAGER->findImage("playerBackBar")->render(Vector2(WINSIZEX / 2 - 275.0f, frameHp->getHeight() / 3.0f));

			expBar->render();
			frameHp->setScale(0.7f);
			frameHp->render(Vector2(WINSIZEX / 2 - 320.0f, frameHp->getHeight() / 2.8f));

			for (int i = 0; i < digitNum; i++)
			{
				hpDigit->setScale(0.7f);
				hpDigit->render(Vector2((float)(WINSIZEX / 2 - 400) + (i * (hpDigit->getWidth() / 2.25f)), frameHp->getHeight() / 3.8f));
			}

			char moneyStr[50];
			sprintf_s(moneyStr, "%07.02f", money);
			D2D_RENDERER->renderText(
				WINSIZEX / 2 - 385, frameHp->getHeight() / 2 - 5,
				stringTOwsting(moneyStr),
				17,
				D2DRenderer::DefaultBrush::White,
				DWRITE_TEXT_ALIGNMENT_LEADING,
				L"메이플스토리"
			);
		}
	}
};

struct tagLevelInfo
{
	Image*		playerLevelUp;
	Image*		leftLevelUp;
	Animation*	playerAni;
	Animation*	leftAni;
	Image*		levelFrame;
	Vector3		pos;
	bool		active;		

	HRESULT init()
	{
		playerLevelUp = IMAGE_MANAGER->findImage("levelUp");
		leftLevelUp = IMAGE_MANAGER->findImage("levelUp");
		playerAni = new Animation;
		playerAni->init(playerLevelUp->getWidth(), playerLevelUp->getHeight(), 4, 1);
		playerAni->setDefPlayFrame();
		playerAni->setFPS(1);

		return S_OK;
	}
	void update(const Vector3& playerPos)
	{
		if (active)
		{
			pos = playerPos;
			

			playerAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);	
			
			if (!playerAni->isPlay())
			{
				active = false;
			}
		}
	}
	void render()
	{
		if (active)
		{
			CAMERA_MANAGER->aniRender(playerLevelUp, pos, playerAni);
		}
	}
};

struct tagBossInfo
{	
	Image*			frameHp;	// 보스 체력 프레임
	ProgressBar*	bossBar;	// 보스 체력 프로그레스바
	float			currentHp;	// 현재 체력
	float			maxHp;		// 최대 체력
	Vector2			pos;		// 좌표
	bool			active;		// 출력 및 업데이트 여부

	HRESULT init()
	{
		bossBar = new ProgressBar;
		frameHp = IMAGE_MANAGER->findImage("bossHpFrame");
		bossBar->init("bossBackBar", "bossFrontBar", Vector2(WINSIZEX / 2 - 58, WINSIZEY - 95), Vector2(-15.0f, 0.0f));	// 보스 체력 위치설정

		return S_OK;
	}
	void update()
	{
		if (active)
		{
			bossBar->update();
			bossBar->setGauge(currentHp, maxHp);
		}
	}
	void render()
	{
		if (active)
		{
			bossBar->render();
			frameHp->render(Vector2(WINSIZEX / 2, WINSIZEY - 100));
		}
	}
};

enum class DOOR_STATE
{
	LOCK, UNLOCK, SHOP	// 잠금, 열림, 상점
};

struct tagDoorInfo
{		
	DOOR_STATE	doorState;	// 현재 문 상태
	Vector3		pos;		// 좌표

	HRESULT init(DOOR_STATE state, const Vector3& doorPos)
	{
		doorState = state;
		pos = doorPos;
		scale = 0.7f;
		alpha = 1.0f;

		switch (doorState)
		{
			case DOOR_STATE::LOCK:
			{
				img = IMAGE_MANAGER->findImage("lockDoor"); 
				break;
			}
			case DOOR_STATE::UNLOCK:
			{
				img = IMAGE_MANAGER->findImage("unlockDoor");
				break;
			}			
			case DOOR_STATE::SHOP:
			{
				img = IMAGE_MANAGER->findImage("shopDoor");
				break;
			}			
		}
		
		return S_OK;
	}
	void update(const Vector3& playerPos)
	{
		float distance = Vector3::distance(pos, playerPos);

		switch (distance < 250.0f)
		{
			case 0:	// 문과 멀다
			{
				// 스케일
				if (scale > 0.6f)
					scale -= 0.02f;
				else
					scale = 0.6f;
				// 알파값
				if (alpha < 0.3f)
					alpha = 0.3f;
				else
					alpha -= 0.05f;

				break;
			}
			case 1:	// 문과 가깝다
			{
				// 스케일
				if (scale < 0.8f)
					scale += 0.02f;
				else
					scale = 0.8f;
				// 알파값
				if (alpha > 1.0f)
					alpha = 1.0f;
				else
					alpha += 0.05f;

				break;
			}
		}		
	}
	void render()
	{
		img->setAlpha(alpha);
		img->setScale(scale);
		CAMERA_MANAGER->render(img, CAMERA_MANAGER->convertV3ToV2(pos));
	}

private:
	Image*		img;		// 이미지
	float		scale;		// 스케일
	float		alpha;		// 알파값
};

struct tagHeartInfo
{
	bool	active;	// 출력 여부

	HRESULT init(int loopCount)
	{
		img = IMAGE_MANAGER->findImage("heart");
		black = IMAGE_MANAGER->findImage("blackScreen");
		loading = IMAGE_MANAGER->findImage("loading");		

		maxLoop = loopCount;
		scale = 3.0f;
		curFrame = active = 0;
		curLoop = 1;
		elapseT = 4.0f;

		return S_OK;
	}
	void update(class Player* player)
	{
		if (active)
		{
			playerPos = CAMERA_MANAGER->getRelativeV2(CAMERA_MANAGER->convertV3ToV2(player->getPosition()));

			heartRc = rectMakePivot(playerPos, Vector2(img->getWidth() * scale, img->getHeight() * scale), Pivot::Center);

			if(scale > 0) scale -= 0.02f;
			else
			{
				isLoading = true;
			}
			if (isLoading)
			{
				elapseT -= TIME_MANAGER->getElapsedTime() * 10;
				if (elapseT <= 0)
				{
					elapseT = 4.0f;
					if (curFrame < loading->getMaxFrameX() - 1) curFrame++;
					else
					{
						curFrame = 0;
						curLoop++;
					}
				}				

				if (curLoop == maxLoop)
				{
					isLoading = false;
					active = false;
					curLoop = 1;
					curFrame = 0;
					scale = 3.0f;
				}
			}
		}		
	}
	void render()
	{
		if (active)
		{
			img->setScale(scale);
			img->render(playerPos);			

			// 하트 외부에 검은화면 좌표 및 사이즈 계산용 렉트
			FloatRect rcR = rectMakePivot(Vector2(heartRc.right - 10, 0.0f), Vector2(WINSIZEX - heartRc.right + 10, (float)WINSIZEY), Pivot::LeftTop);
			FloatRect rcL = rectMakePivot(Vector2(0, 0), Vector2(heartRc.left + 10, (float)WINSIZEY), Pivot::LeftTop);
			FloatRect rcT = rectMakePivot(Vector2(0, 0), Vector2((float)WINSIZEX, heartRc.top + 10), Pivot::LeftTop);
			FloatRect rcB = rectMakePivot(Vector2(0.0f, heartRc.bottom - 10), Vector2((float)WINSIZEX, WINSIZEY - heartRc.bottom), Pivot::LeftTop);

			black->setSize(rcR.getSize());
			black->render(rcR.getCenter());

			black->setSize(rcL.getSize());
			black->render(rcL.getCenter());

			black->setSize(rcT.getSize());
			black->render(rcT.getCenter());

			black->setSize(rcB.getSize());
			black->render(rcB.getCenter());	

			if (isLoading)
			{
				loading->frameRender(Vector2(WINSIZEX - loading->getFrameSize().x / 2 - 20, WINSIZEY - loading->getFrameSize().y / 2 - 20), curFrame, 0);
			}
		}
	}

private:
	Image*		img;		// 하트
	Image*		black;		// 검정 화면
	Image*		loading;	// 로딩 프레임
	Vector2		playerPos;	// 플레이어 위치
	FloatRect	heartRc;	// 하트 좌표 확인용 렉트
	Animation*	ani;		// 애니렌더 사용
	float		scale;		// 스케일
	int			curLoop;	// 현재 루프
	int			maxLoop;	// 최대 루프
	int			curFrame;	// 현재 프레임
	float		elapseT;	// 시간 계산용
	bool		isLoading;	// 로딩창 출력 여부
};

struct tagShopInfo
{
private:
	float		money;					// 돈
	float		scale;					// 스케일
	int			currentList;			// 현재 아이템
	FloatRect	itemPos[SHOPLISTMAX];	// 아이템 리스트 포지션
	Vector2		buttonPos, movePos;		// 버튼 위치, 버튼이 이동해야할 위치
	Image*		itemList[SHOPLISTMAX];	// 아이템 이미지
	Image*		selectBar;				// 선택된 것
	Image*		buyButton;				// 버튼
	bool		isPurchase;				// 구매중?

	struct tagItemInfo		// 아이템 정보 구조체
	{
		string	name;		// 이름
		float	price;		// 가격
		float	recovery;	// 아이템 회복 효과
	};

	vector<tagItemInfo> vItem;

public:
	bool		active;

	HRESULT init()
	{
		currentList = 0;

		selectBar = IMAGE_MANAGER->findImage("shopSelectBar");
		buyButton = IMAGE_MANAGER->findImage("shop_BuyButton");
		scale = 0.72f;

		// 먼저 초기 위치 잡아줌
		itemPos[0] = rectMakePivot(Vector2(WINSIZEX / 2 + 395, WINSIZEY / 2 - 85), Vector2(selectBar->getWidth() * scale, selectBar->getHeight() * scale), Pivot::Center);
		for (int i = 1; i < SHOPLISTMAX; i++)
		{
			// 위에 렉트를 기준으로 위치 설정
			itemPos[i] = rectMakePivot(Vector2(itemPos[i - 1].getCenter().x - 16, itemPos[i - 1].getCenter().y + 86), Vector2(selectBar->getWidth() * scale, selectBar->getHeight() * scale), Pivot::Center);
		}
		for (int i = 0; i < SHOPLISTMAX; i++)
		{
			tagItemInfo item;

			string section = "item_" + to_string(i + 1);
			char result[100];

			GetPrivateProfileString(section.c_str(), "name", "error", result, 100, "resources/images/UI/shop/item.ini");
			item.name = result;
			GetPrivateProfileString(section.c_str(), "price", "error", result, 100, "resources/images/UI/shop/item.ini");
			item.price = atof(result);
			GetPrivateProfileString(section.c_str(), "notice", "error", result, 100, "resources/images/UI/shop/item.ini");
			item.recovery = atof(result);

			vItem.push_back(item);

			itemList[i] = IMAGE_MANAGER->findImage("item_" + to_string(i + 1));			
		}
		return S_OK;
	}
	void update(class Player* player)
	{
		if (active)
		{
			money = player->getMoney();			

			if (KEY_MANAGER->isOnceKeyDown(VK_DOWN))
			{				
				SOUND_MANAGER->stop("UI_scroll");
				SOUND_MANAGER->play("UI_scroll");
				if (++currentList >= SHOPLISTMAX) currentList = 0;
			}
			if (KEY_MANAGER->isOnceKeyDown(VK_UP))
			{				
				SOUND_MANAGER->stop("UI_scroll");
				SOUND_MANAGER->play("UI_scroll");
				if (--currentList < 0) currentList = SHOPLISTMAX - 1;
			}
			if (KEY_MANAGER->isOnceKeyDown('X'))
			{				
				SOUND_MANAGER->stop("UI_cancel");
				SOUND_MANAGER->play("UI_cancel");
				active = false;
			}
			if (KEY_MANAGER->isOnceKeyDown('Z'))
			{				
				// 돈이 부족하면 살 수 없음
				if (money >= vItem[currentList].price && player->getHp() < player->getMaxHp())
				{
					SOUND_MANAGER->stop("UI_confirm");
					SOUND_MANAGER->play("UI_confirm");
					// 돈계산
					player->setMoney(money - vItem[currentList].price);
					// 체력 회복	
					player->setHp(player->getHp() + (vItem[currentList].recovery * player->getMaxHp() / 100));
					// 최대 체력 초과 방지
					if (player->getHp() > player->getMaxHp()) player->setHp(player->getMaxHp());
				}		
				else
				{
					SOUND_MANAGER->stop("UI_cancel");
					SOUND_MANAGER->play("UI_cancel");
				}
			}
		}
	}
	void render()
	{
		if (active)
		{			
			// 상점 전체 이미지 출력
			IMAGE_MANAGER->findImage("shopFrame")->setSize(Vector2(WINSIZEX, WINSIZEY));
			IMAGE_MANAGER->findImage("shopFrame")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2));
			
			// 선택 창 출력
			selectBar->setScale(scale);
			selectBar->render(itemPos[currentList].getCenter());
			
			// 아이템 이미지 출력
			itemList[currentList]->render(Vector2(itemPos[currentList].getCenter().x - 200, itemPos[currentList].getCenter().y - 50));

			// 돈 출력
			char moneyStr[20];
			sprintf_s(moneyStr, "$%.2f", money);
			D2D_RENDERER->renderText(
				WINSIZEX - 210, WINSIZEY / 2 - 180,
				stringTOwsting(moneyStr),
				27,
				D2DRenderer::DefaultBrush::White,
				DWRITE_TEXT_ALIGNMENT_LEADING,
				L"메이플스토리",
				10.0f
			);

			for (int i = 0; i < vItem.size(); i++)
			{				
				// 아이템 이름 출력
				D2D_RENDERER->renderText(
					itemPos[i].getCenter().x - 150, itemPos[i].getCenter().y - 70,								// 출력 좌표
					stringTOwsting(vItem[i].name),																// 출력할 텍스트
					25,																							// 폰트 크기
					i == currentList ? D2DRenderer::DefaultBrush::White : D2DRenderer::DefaultBrush::Black,		// 선택되어있으면 흰색, 아니면 검정색
					DWRITE_TEXT_ALIGNMENT_LEADING,																// 정렬
					L"메이플스토리",																				// 폰트
					10.0f																						// 회전 각도
				);
				// 아이템 가격 출력
				char temp[50];
				sprintf_s(temp, "$%.2f", vItem[i].price);				
				D2D_RENDERER->renderText(
					itemPos[i].getCenter().x + 100, itemPos[i].getCenter().y - 30,
					stringTOwsting(temp),
					25,
					i == currentList ? D2DRenderer::DefaultBrush::White : D2DRenderer::DefaultBrush::Black,
					DWRITE_TEXT_ALIGNMENT_LEADING,
					L"메이플스토리",
					10.0f
				);
				// 아이템 효과 출력
				sprintf_s(temp, "체력을 %.0f%% 회복시킨다", vItem[i].recovery);
				D2D_RENDERER->renderText(
					itemPos[i].getCenter().x - 153, itemPos[i].getCenter().y - 38,
					stringTOwsting(temp),
					18,
					i == currentList ? D2DRenderer::DefaultBrush::White : D2DRenderer::DefaultBrush::Black,
					DWRITE_TEXT_ALIGNMENT_LEADING,
					L"메이플스토리",
					10.0f
				);				
			}
		}
	}
};

// 숫자가 작을 수록 자물쇠가 부서짐
enum class LOCK_STATE : int
{
	LOCK_4 = 4,		
	LOCK_3 = 3,
	LOCK_2 = 2,
	LOCK_1 = 1,
	LOCK_0 = 0,
	NORMAL = -1
};

struct tagLockInfo
{	
private:
	struct tagChainInfo
	{	
	private:
		Image*		img;
		Vector2		pos;
		Vector2		size;
		Animation*	ani;

		float fps;

	public:
		HRESULT init(const string imageName, const Vector2& position, const Vector2& setSize)
		{
			img = IMAGE_MANAGER->findImage(imageName);

			pos = position;
			size = setSize;

			ani = new Animation;
			ani->init(img->getWidth(), img->getHeight(), img->getMaxFrameX(), img->getMaxFrameY());
			ani->setDefPlayFrame();
			ani->setFPS(1);
			ani->start();

			return S_OK;
		}
		void update()
		{
			ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);
		}
		void render()
		{
			img->setSize(size);
			img->aniRender(pos, ani);
		}
	};
	
	tagChainInfo chainLeft, chainRight;
	tagChainInfo chainTop, chainBottom;

	Image*		img;
	Animation*	ani;
	Vector2		pos;

	LOCK_STATE	curState;

	bool active;

	void chainSetting(string lockSt)
	{
		chainTop.init(
			lockSt + "_top",
			Vector2(WINSIZEX / 2.0f, 100 + IMAGE_MANAGER->findImage(lockSt + "_top")->getFrameSize().y / 2),
			Vector2((float)WINSIZEX, IMAGE_MANAGER->findImage(lockSt + "_top")->getFrameSize().y)
		);

		chainBottom.init(
			lockSt + "_bot",
			Vector2(WINSIZEX / 2.0f, WINSIZEY - (100 + (IMAGE_MANAGER->findImage(lockSt + "_bot")->getFrameSize().y / 2))),
			Vector2((float)WINSIZEX, IMAGE_MANAGER->findImage(lockSt + "_bot")->getFrameSize().y)
		);

		chainLeft.init(
			lockSt + "_left",
			Vector2(IMAGE_MANAGER->findImage(lockSt + "_left")->getFrameSize().x / 2, WINSIZEY / 2.0f),
			Vector2(IMAGE_MANAGER->findImage(lockSt + "_left")->getFrameSize().x, (float)WINSIZEY - 200)
		);

		chainRight.init(
			lockSt + "_right",
			Vector2(WINSIZEX - (IMAGE_MANAGER->findImage(lockSt + "_right")->getFrameSize().x / 2), (WINSIZEY) / 2.0f),
			Vector2(IMAGE_MANAGER->findImage(lockSt + "_right")->getFrameSize().x, (float)WINSIZEY - 200)
		);
	}

public:	

	void init(LOCK_STATE state)
	{		
		if (state == LOCK_STATE::NORMAL)
		{
			active = false;
			curState = LOCK_STATE::NORMAL;
			return;
		}
		else if (state == curState) return;
		switch (state)
		{
			case LOCK_STATE::LOCK_4: case LOCK_STATE::LOCK_3: 
			case LOCK_STATE::LOCK_2: case LOCK_STATE::LOCK_1:
			{
				if(active) break;

				active = true;
				chainSetting("chainLock");				
				break;
			}
			case LOCK_STATE::LOCK_0:
			{								
				chainSetting("chainUnlock");
				break;
			}			
		}		
		
		switch (state)
		{
			case LOCK_STATE::LOCK_4: img = IMAGE_MANAGER->findImage("lock_4"); break;
			case LOCK_STATE::LOCK_3: img = IMAGE_MANAGER->findImage("lock_3"); break;
			case LOCK_STATE::LOCK_2: img = IMAGE_MANAGER->findImage("lock_2"); break;
			case LOCK_STATE::LOCK_1: img = IMAGE_MANAGER->findImage("lock_1"); break;
			case LOCK_STATE::LOCK_0: img = IMAGE_MANAGER->findImage("lock_0"); break;
		}
		
		ani = new Animation;
		ani->init(img->getWidth(), img->getHeight(), img->getMaxFrameX(), img->getMaxFrameY());
		ani->setDefPlayFrame();
		ani->setFPS(1);
		ani->start();
		

		curState = state;

		pos = Vector2(WINSIZEX / 2.0f, 120 + img->getFrameSize().x / 2);		
	}
	void update()
	{
		if (active)
		{
			chainLeft.update(); 
			chainRight.update();
			chainTop.update(); 
			chainBottom.update();	

			ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

			if (curState == LOCK_STATE::LOCK_0 && !ani->isPlay())
			{
				curState = LOCK_STATE::NORMAL;
				active = false;
			}
		}
	}
	void render()
	{
		if (active)
		{
			chainLeft.render(); 
			chainRight.render();
			chainTop.render(); 
			chainBottom.render();

			img->aniRender(pos, ani);
		}
	}
};

struct tagCellPhone
{
	Image* phoneImg;
	float x, y;
	bool active;
	float height;	
};

class UIManager
{
private:
	tagPlayerInfo	_playerInfo;
	tagLevelInfo	_levelInfo;
	tagBossInfo		_bossInfo;
	tagCellPhone	_cellPhone;
	tagHeartInfo	_heart;
	tagShopInfo		_shop;	
	tagLockInfo		_lock;

	vector<tagDoorInfo> _vDoor;

	class Player* _player;

public:
	UIManager();
	~UIManager();

	HRESULT init(class Player* player);
	void release();
	void update();
	void render();	

	// 플레이어 체력 및 경험치
	void setPlayerHpActive(bool active)					{ _playerInfo.active = active; }
	void setPlayerHp(float currentHp, float maxHp)		{ _playerInfo.currentHp = currentHp; _playerInfo.maxHp = maxHp; }
	void setPlayerExp(float currentExp, float maxExp)	{ _playerInfo.currentExp = currentExp; _playerInfo.maxExp = maxExp; }

	// 레벨업 출력
	void setLevelUp(bool active);	

	// 보스 체력
	void setBossHpActive(bool active)				{ _bossInfo.active = active; }
	void setBossHp(float currentHp, float maxHp)	{ _bossInfo.currentHp = currentHp; _bossInfo.maxHp = maxHp; }

	// 문 세팅
	void setDoor(vector<tagDoorInfo> doors);

	void setHeart(bool active)	{ _heart.active = active; }
	bool getHeart()				{ return _heart.active; }

	void setShopUI(bool active) { _shop.active = active; }
	bool getShopUI()			{ return _shop.active; }

	void setLock(LOCK_STATE state);
};

