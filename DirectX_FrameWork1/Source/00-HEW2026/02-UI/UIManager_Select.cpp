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
    GameObject* pPanel = nullptr;       //真ん中
    GameObject* pPrevPanel = nullptr;   //左側（前）
    GameObject* pNextPanel = nullptr;   //右側（次）

    UI rightButton;
    UI leftButton;
    UI decisionButton;
    UI titleButton;

    // 画像パス
    std::vector<std::string> stagePaths;
    int currentIdx = 0;

    int se_select = -1;
    int se_decide = -1;

    void UpdateImages()
    {
        int total = (int)stagePaths.size();
        if (total == 0) return;

        // 真ん中 (常に表示)
        if (auto r = pPanel->GetComponent<SpriteRenderer>())
        {
            r->LoadTexture(stagePaths[currentIdx].c_str());
        }

        // 左側 (前のステージ)
        if (auto r = pPrevPanel->GetComponent<SpriteRenderer>())
        {
            // 0より大きい（前のステージがある）なら表示
            if (currentIdx > 0)
            {
                r->SetIsActive(true); // 表示
                r->LoadTexture(stagePaths[currentIdx - 1].c_str());
            }
            else
            {
                r->SetIsActive(false); // 端っこなので非表示
            }
        }

        // 右側 (次のステージ)
        if (auto r = pNextPanel->GetComponent<SpriteRenderer>())
        {
            // サイズ-1 より小さい（次のステージがある）なら表示
            if (currentIdx < total - 1)
            {
                r->SetIsActive(true); // 表示
                r->LoadTexture(stagePaths[currentIdx + 1].c_str());
            }
            else
            {
                r->SetIsActive(false); // 端っこなので非表示
            }
        }

    }

public:
    StageSelectLogic() { tag = "StageSelectLogic"; }
    ~StageSelectLogic()
    {
        // newしたものdeleteする
        if (pPanel) delete pPanel;
        if (pPrevPanel) delete pPrevPanel;
        if (pNextPanel) delete pNextPanel;
    }

    void Init() override
    {
        //背景設定
        pBGImg = new SimpleObject();
        pBGImg->AddComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/01-Map/BGImg600.png");

        hft::HFFLOAT2 windowSize = Application::GetInstance().GetWindowSize();
        pBGImg->GetTransformPtr()->scale = { windowSize.x,windowSize.y,1 };
        pBGImg->GetTransformPtr()->position.z = 100;

        // 画像パス設定
        stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
        stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
        stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
        stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
        stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
        stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");

        // ---------------------------------------------------
        // 真ん中
        // ---------------------------------------------------
        pPanel = new SimpleObject();
        pPanel->AddComponent<SpriteRenderer>();
        pPanel->GetTransformPtr()->position = { 0.0f, 0.0f, 0.0f };
        pPanel->GetTransformPtr()->scale = { 450.0f, 450.0f, 1.0f };

        // ---------------------------------------------------
        // 左側 (プレビュー)
        // ---------------------------------------------------
        hft::HFFLOAT3 scl = { 250,250,1 };
        hft::HFFLOAT3 pos = { 450,0,0 };
        pPrevPanel = new SimpleObject();
        pPrevPanel->AddComponent<SpriteRenderer>();
        pPrevPanel->GetTransformPtr()->position = { -450, pos.y, pos.z };
        pPrevPanel->GetTransformPtr()->scale = scl;

        // ---------------------------------------------------
        // 右側 (プレビュー)
        // ---------------------------------------------------
        pNextPanel = new SimpleObject();
        pNextPanel->AddComponent<SpriteRenderer>();
        pNextPanel->GetTransformPtr()->position = pos;
        pNextPanel->GetTransformPtr()->scale = scl;


        // 最初の表示更新
        UpdateImages();

        // 音の読み込み
        se_select = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/10-UI/StageSelect_Swap.wav", false);
        se_decide = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/10-UI/Decision.wav", false);

        hft::HFFLOAT3 arrowScl = { 200,150,1 };
        hft::HFFLOAT3 arrowPos = { pos.x + 300,0,-10 };
        rightButton.Init(arrowPos, arrowScl, "Assets/01-Texture/02-Player/Arrow.png", Type_UI::ButtonType);
        arrowPos.x *= -1;
        leftButton.Init(arrowPos, arrowScl, "Assets/01-Texture/02-Player/Arrow.png", Type_UI::ButtonType);
        leftButton.GetTransformPtr()->rotation.y = 180;
        decisionButton.Init({ 0,-350,-10 }, { 400.f,160.f }, "Assets/01-Texture/02-Player/Arrow.png", Type_UI::ButtonType);
        titleButton.Init({ 500,-400,-10 }, { 300,150 }, "Assets/01-Texture/10-UI/10-Title/Button_Title.png", Type_UI::ButtonType);
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