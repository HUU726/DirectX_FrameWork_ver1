#include "UIManager_Select.h"

#include "../../02-App/Application.h"

#include "../10-Map/99-MapDataManager/MapDataManager.h"
#include "../../99-Lib/01-MyLib/08-Scene/02-SceneManager/SceneManager.h"
#include "../../99-Lib/01-MyLib/03-Sound/Fsound.h"
#include "../20-Scene/03_GameScene.h"
#include "../20-Scene/01_Hew_TitleScene.h"

class SimpleObject : public GameObject
{
public:
    void Init() override {}
    void Update() override {}
};

// ============================================================================
// ステージ選択ロジック
// ============================================================================
class StageSelectLogic : public GameObject
{
private:
    // --- 表示物 ---
    GameObject* pBGImg = nullptr;       //背景

    GameObject* pStage = nullptr;       //真ん中
    GameObject* pPrevStage = nullptr;   //左側（前）
    GameObject* pNextStage = nullptr;   //右側（次）

    GameObject* pName = nullptr;
    GameObject* pPreName = nullptr;
    GameObject* pNextName = nullptr;

    GameObject* pPanel = nullptr;       //真ん中
    GameObject* pPrevPanel = nullptr;   //左側（前）
    GameObject* pNextPanel = nullptr;   //右側（次）


    UI rightButton;
    UI leftButton;
    UI decisionButton;
    UI titleButton;

    // 画像パス
    std::vector<std::string> stageNames;
    std::vector<std::string> stagePaths;
    int currentIdx = 0;

    int se_select = -1;
    int se_decide = -1;

    void UpdateImages()
    {
        int total = (int)stagePaths.size();
        if (total == 0) return;

        // 真ん中 (常に表示)
        if (auto r = pStage->GetComponent<SpriteRenderer>())
        {
            pName->GetComponent<SpriteRenderer>()->LoadTexture(stageNames[currentIdx].c_str());
            r->LoadTexture(stagePaths[currentIdx].c_str());
        }

        // 左側 (前のステージ)
        if (auto r = pPrevStage->GetComponent<SpriteRenderer>())
        {
            // 0より大きい（前のステージがある）なら表示
            if (currentIdx > 0)
            {
                pPrevPanel->GetComponent<SpriteRenderer>()->SetIsActive(true);
                r->SetIsActive(true); // 表示
                r->LoadTexture(stagePaths[currentIdx - 1].c_str());
            }
            else
            {
                pPrevPanel->GetComponent<SpriteRenderer>()->SetIsActive(false);
                r->SetIsActive(false); // 端っこなので非表示
            }
        }

        // 右側 (次のステージ)
        if (auto r = pNextStage->GetComponent<SpriteRenderer>())
        {
            // サイズ-1 より小さい（次のステージがある）なら表示
            if (currentIdx < total - 1)
            {
                pNextPanel->GetComponent<SpriteRenderer>()->SetIsActive(true);
                r->SetIsActive(true); // 表示
                r->LoadTexture(stagePaths[currentIdx + 1].c_str());
            }
            else
            {
                pNextPanel->GetComponent<SpriteRenderer>()->SetIsActive(false);
                r->SetIsActive(false); // 端っこなので非表示
            }
        }

    }

public:
    StageSelectLogic() { tag = "StageSelectLogic"; }
    ~StageSelectLogic()
    {
        // newしたものdeleteする
        if (pStage) delete pStage;
        if (pPrevStage) delete pPrevStage;
        if (pNextStage) delete pNextStage;
        if (pPanel) delete pPanel;
        if (pPrevPanel) delete pPrevPanel;
        if (pNextPanel) delete pNextPanel;
        if (pName) delete pName;
    }

    void Init() override
    {
        //背景設定
        pBGImg = new SimpleObject();
        pBGImg->AddComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/20-BGImg/02-Select/BGImg_Select.png");

        hft::HFFLOAT2 windowSize = Application::GetInstance().GetWindowSize();
        pBGImg->GetTransformPtr()->scale = { windowSize.x,windowSize.y,1 };
        pBGImg->GetTransformPtr()->position.z = 100;

        // 画像パス設定
        {   //ステージ画像
            stagePaths.push_back("Assets/01-Texture/10-UI/11-Select/Tutorialpreview.png");
            stagePaths.push_back("Assets/01-Texture/10-UI/11-Select/Stage1preview.png");
            stagePaths.push_back("Assets/01-Texture/10-UI/11-Select/Stage2preview.png");
            stagePaths.push_back("Assets/01-Texture/10-UI/11-Select/Stage3preview.png");
            stagePaths.push_back("Assets/01-Texture/10-UI/11-Select/Stage4preview.png");
            stagePaths.push_back("Assets/01-Texture/10-UI/11-Select/Stage5preview.png");
            stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
            stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
            stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
            stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
        }
        {   //ステージ名画像
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Tutorial_1.png");
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Stage_1.png");
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Stage_2.png");
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Stage_3.png");
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Stage_4.png");
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Stage_5.png");
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Stage_6.png");
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Stage_7.png");
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Stage_8.png");
            stageNames.push_back("Assets/01-Texture/10-UI/11-Select/UI_SelectView_Stage_9.png");
        }

        // ---------------------------------------------------
        // 真ん中
        // ---------------------------------------------------
        pStage = new SimpleObject();
        pStage->AddComponent<SpriteRenderer>();
        pStage->GetTransformPtr()->position = { 0.0f, 100.f, 0.0f };
        pStage->GetTransformPtr()->scale = { 700.0f, 450.0f, 1.0f };

        pName = new SimpleObject();
        pName->AddComponent<SpriteRenderer>();
        pName->GetTransformPtr()->position = { 0,380,-50 };
        pName->GetTransformPtr()->scale = { 500,200,1 };

        pPanel = new SimpleObject();
        pPanel->AddComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/10-UI/11-Select/UI_SelectView_stage.png");
        pPanel->GetTransformPtr()->position = { 0,100,-20 };
        pPanel->GetTransformPtr()->scale = { 900,650,1 };

        // ---------------------------------------------------
        // 左側 (プレビュー)
        // ---------------------------------------------------
        hft::HFFLOAT3 scl = { 600,300,1 };
        hft::HFFLOAT3 pos = { 1100,100,0 };
        pPrevStage = new SimpleObject();
        pPrevStage->AddComponent<SpriteRenderer>();
        pPrevStage->GetTransformPtr()->position = { -pos.x, pos.y, pos.z };
        pPrevStage->GetTransformPtr()->scale = scl;

        pPrevPanel = new SimpleObject();
        pPrevPanel->AddComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/10-UI/11-Select/UI_SelectView_stage.png");
        pPrevPanel->GetTransformPtr()->position = { -pos.x,pos.y,pos.z-1 };
        pPrevPanel->GetTransformPtr()->scale = { 750,500,1 };

        // ---------------------------------------------------
        // 右側 (プレビュー)
        // ---------------------------------------------------
        pNextStage = new SimpleObject();
        pNextStage->AddComponent<SpriteRenderer>();
        pNextStage->GetTransformPtr()->position = pos;
        pNextStage->GetTransformPtr()->scale = scl;

        pNextPanel = new SimpleObject();
        pNextPanel->AddComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/10-UI/11-Select/UI_SelectView_stage.png");
        pNextPanel->GetTransformPtr()->position = { pos.x,pos.y,pos.z - 1 };
        pNextPanel->GetTransformPtr()->scale = { 750,500,1 };


        // 最初の表示更新
        UpdateImages();

        // 音の読み込み
        SoundManager& soundMng = SoundManager::GetInstance();
        se_select = soundMng.AddSoundDirect("Assets/03-Sound/10-UI/StageSelect_Swap.wav", false);
        se_decide = soundMng.AddSoundDirect("Assets/03-Sound/10-UI/Decision.wav", false);

        soundMng.SetVolume(se_decide, 0.1f);

        //ボタン系
        hft::HFFLOAT3 arrowScl = { 150,150,1 };
        hft::HFFLOAT3 arrowPos = { 680,-200,-10 };
        rightButton.Init(arrowPos, arrowScl, "Assets/01-Texture/10-UI/11-Select/UI_SelectView_Arrow.png", Type_UI::ButtonType);
        rightButton.GetTransformPtr()->rotation.y = 180;
        arrowPos.x *= -1;
        leftButton.Init(arrowPos, arrowScl, "Assets/01-Texture/10-UI/11-Select/UI_SelectView_Arrow.png", Type_UI::ButtonType);
        decisionButton.Init({ 0,-380,-10 }, { 600.f,270.f }, "Assets/01-Texture/10-UI/11-Select/UI_SelectView_Challenge.png", Type_UI::ButtonType);
        titleButton.Init({ 730,-470,-10 }, { 300,150 }, "Assets/01-Texture/10-UI/11-Select/UI_SelectView_title.png", Type_UI::ButtonType);
    }

    void Update() override
    {
        Input& input = Input::GetInstance();
        bool isChanged = false;

        // 右入力
        if (input.GetKeyTrigger('D') || input.GetKeyTrigger(0x27) || input.GetLeftAnalogStick().x > 0.5f || rightButton.GetIsTrigger())
        {
            // 次がある場合のみ進む
            if (currentIdx < stagePaths.size() - 1)
            {
                currentIdx++;
                isChanged = true;
            }
        }
        // 左入力
        else if (input.GetKeyTrigger('A') || input.GetKeyTrigger(0x25) || input.GetLeftAnalogStick().x < -0.5f || leftButton.GetIsTrigger())
        {
            // 前がある場合のみ戻る
            if (currentIdx > 0)
            {
                currentIdx--;
                isChanged = true;
            }
        }

        if (isChanged)
        {
            UpdateImages();
            SoundManager::GetInstance().Play(se_select);
        }

        // 決定
        if (input.GetKeyTrigger(0x20) || input.GetButtonTrigger(Button::XBox::A) || decisionButton.GetIsTrigger())
        {
            SoundManager::GetInstance().Play(se_decide);

            MapDataManager::GetInstance().SetMapID(currentIdx);
            SceneManager::GetInstance().LoadScene<Hew_GameScene>();
        }

        if (titleButton.GetIsPressed())
            SceneManager::GetInstance().LoadScene<Hew_TitleScene>();
    }
};





StageSelectUIManager::~StageSelectUIManager()
{
    if (pLogic)
    {
        delete static_cast<StageSelectLogic*>(pLogic);
        pLogic = nullptr;
    }
}

//ステージセレクトシーン管理の処理=======================================================
void StageSelectUIManager::Init()
{
    // ロジックオブジェクトを生成
    pLogic = new StageSelectLogic();
    pLogic->Init();
}

void StageSelectUIManager::Update()
{

}