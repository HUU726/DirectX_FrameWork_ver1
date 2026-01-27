#include "StageSelectScene.h"

#include "../../06-GameObject/GameObject.h"
#include "../../../../04-Input/Input.h"
#include "../../03-Sound/Fsound.h"
#include "../02-SceneManager/SceneManager.h"
#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"

#include "../../07-Component/04-Camera/01-Camera2D/Camera2D.h"
#include "../../07-Component/04-Camera/02-Camera3D/Camera3D.h"

#include "../../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"
#include "../../07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"

#include "../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"

#include "../../101-Time/Time.h"

// 次のシーン（ゲーム本編）をインクルード
#include "GameScene.h" 
#include "TitleScene.h"

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
    GameObject* pPanel = nullptr;  // 真ん中
    GameObject* pPrevPanel = nullptr;  // 左側（前）
    GameObject* pNextPanel = nullptr;  // 右側（次）

    GameObject* pArrowLeft = nullptr;
    GameObject* pArrowRight = nullptr;

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

        if (auto r = pArrowLeft->GetComponent<SpriteRenderer>())
            r->SetIsActive(currentIdx > 0);

        if (auto r = pArrowRight->GetComponent<SpriteRenderer>())
            r->SetIsActive(currentIdx < total - 1);
    }

public:
    StageSelectLogic() { tag = "StageSelectLogic"; }
    ~StageSelectLogic()
    {
        // newしたものdeleteする
        if (pPanel) delete pPanel;
        if (pPrevPanel) delete pPrevPanel;
        if (pNextPanel) delete pNextPanel;
        if (pArrowLeft) delete pArrowLeft;
        if (pArrowRight) delete pArrowRight;
    }

    void Init() override
    {
        // 画像パス設定
        stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
        stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");
        stagePaths.push_back("Assets/01-Texture/99-Test/wave.png");

        // ---------------------------------------------------
        // 真ん中
        // ---------------------------------------------------
        pPanel = new SimpleObject();
        pPanel->AddComponent<SpriteRenderer>();
        pPanel->GetTransformPtr()->position = { 0.0f, 0.0f, 0.0f };
        pPanel->GetTransformPtr()->scale = { 400.0f, 250.0f, 1.0f };

        // ---------------------------------------------------
        // 左側 (プレビュー)
        // ---------------------------------------------------
        pPrevPanel = new SimpleObject();
        pPrevPanel->AddComponent<SpriteRenderer>();
        pPrevPanel->GetTransformPtr()->position = { -350.0f, 0.0f, 0.0f };
        pPrevPanel->GetTransformPtr()->scale = { 200.0f, 125.0f, 1.0f };

        // ---------------------------------------------------
        // 右側 (プレビュー)
        // ---------------------------------------------------
        pNextPanel = new SimpleObject();
        pNextPanel->AddComponent<SpriteRenderer>();
        pNextPanel->GetTransformPtr()->position = { 350.0f, 0.0f, 0.0f };
        pNextPanel->GetTransformPtr()->scale = { 200.0f, 125.0f, 1.0f };

        // ---------------------------------------------------
        // 矢印
        // ---------------------------------------------------
        pArrowLeft = new SimpleObject();
        auto rLeft = pArrowLeft->AddComponent<SpriteRenderer>();
        rLeft->LoadTexture("Assets/01-Texture/02-Player/Arrow.png"); //左矢印
        pArrowLeft->GetTransformPtr()->position = { -500.0f, 0.0f, 0.0f };
        pArrowLeft->GetTransformPtr()->scale = { 50.0f, 80.0f, 1.0f };

        pArrowRight = new SimpleObject();
        auto rRight = pArrowRight->AddComponent<SpriteRenderer>();
        rRight->LoadTexture("Assets/01-Texture/02-Player/Arrow.png"); //右矢印
        pArrowRight->GetTransformPtr()->position = { 500.0f, 0.0f, 0.0f };
        pArrowRight->GetTransformPtr()->scale = { 50.0f, 80.0f, 1.0f };

        // 最初の表示更新
        UpdateImages();

        // 音の読み込み
        // se_select = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/10-UI/Select.wav", false);
        // se_decide = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/10-UI/Decide.wav", false);
    }

    void Update() override
    {
        Input& input = Input::GetInstance();
        bool isChanged = false;

        // 右入力
        if (input.GetKeyTrigger('D') || input.GetKeyTrigger(0x27) || input.GetLeftAnalogStick().x > 0.5f)
        {
            // 次がある場合のみ進む
            if (currentIdx < stagePaths.size() - 1)
            {
                currentIdx++;
                isChanged = true;
            }
        }
        // 左入力
        else if (input.GetKeyTrigger('A') || input.GetKeyTrigger(0x25) || input.GetLeftAnalogStick().x < -0.5f)
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
            //SoundManager::GetInstance().Play(se_select);
        }

        // 決定
        if (input.GetKeyTrigger(0x20) || input.GetButtonTrigger(Button::XBox::A))
        {
            //SoundManager::GetInstance().Play(se_decide);
            
            //選んだ番号(currentIdx)を渡して遷移
            //SceneManager::GetInstance().LoadScene(std::make_unique<GameScene>(currentIdx));
            
            //テスト用とりあえずタイトルへ
            SceneManager::GetInstance().LoadScene<TitleScene>();
        }
    }
};

// ============================================================================
// ステージセレクトシーン本体
// ============================================================================

void StageSelectScene::Init()
{
    {	//2Dカメラ初期化
        Transform* p_trf = camera2D.GetTransformPtr();
        p_trf->position = { 0.f,0.f,0.f,0.f };

        Sprite2DRenderer::GetInstance().SetCamera(camera2D.GetComponent<Camera2D>());
    }

    {	//3Dカメラ初期化
        Transform* p_trf = camera3D.GetTransformPtr();
        p_trf->position = { 0.f,0.f,-500.f,0.f };

        Mesh3DRenderer::GetInstance().SetCamera(camera3D.GetComponent<Camera3D>());
    }

    // ロジックオブジェクトを生成
    pLogic = new StageSelectLogic();
    pLogic->Init();
}

void StageSelectScene::UnInit()
{
    if (pLogic)
    {
        delete static_cast<StageSelectLogic*>(pLogic);
        pLogic = nullptr;
    }
}