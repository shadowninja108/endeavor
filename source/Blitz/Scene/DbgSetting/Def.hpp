#pragma once

namespace DbgSetting {

    /* Unofficial. */
    enum Category {
        /* 
            Maps 
            Note: Currently we are targetting a build that doesn't support Octa, so those are commented out. The build also has "inspection" (検) maps, which don't exist on 3.1.0 retail.
        */
        Category_Mission, // ミッション
        // Category_Octa, // オクタ
        // Category_Octa_Stage, // オクタステージ
        Category_Versus, // Versus
        Category_Other, // その他
        Category_Mission_Inspection, // ミッション(検)
        Category_Versus_Inspection, // Versus(検)
        Category_Mission_Test, // ミッション(テ)
        // Category_Octa_Test, // オクタ(テ)
        Category_Versus_Test, // Versus(テ)
        Category_Unclassified, // 未分類

        Category_Scene, // シーン
        Category_Rules, // ルール

        /* Weapons */
        Category_Main, // メイン
        Category_Sub , // サブ
        Category_Special, // スペシャル

        Category_Tanks, // タンク

        /* Gear */
        Category_Headwear, // 被り物
        Category_Clothing, // 服
        Category_Shoes, // 靴

        Category_Skills, // ギアスキル
        Category_OtherPersonalPreferences, // その他個人設定

        /* Convenience constants. */
        Category_StartMap = Category_Mission,
        Category_EndMap = Category_Unclassified,

        Category_StartWeapons = Category_Main,
        Category_EndWeapons = Category_Special,

        Category_StartGear = Category_Headwear,
        Category_EndGear = Category_Shoes,
    };

}


  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
