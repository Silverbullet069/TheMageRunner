
#include "TypingScene.h"

TypingScene::TypingScene()
{
   //
}

TypingScene::~TypingScene()
{
   //
}

void TypingScene::InitBackStory(SDL_Renderer* des, SDL_Event& events)
{
   std::string inter_mono_tmp = "";

   //Scene 1
   for(int i = 0 ; i < TOTAL_INNER_MONO_SCENE_1 ; ++i)
   {
      switch (i)
      {
      case 0 :
         inter_mono_tmp = "Who am I ?";
         break;

      case 1 :
         inter_mono_tmp = "What is my name ?";
         break;

      case 2 :
         inter_mono_tmp = "Where do I come from?";
         break;

      case 3 :
         inter_mono_tmp = "Why can't I remember anything?";
         break;

      case 4 :
         inter_mono_tmp = "So many questions in my head...";
         break;

      case 5 :
         inter_mono_tmp = "but i can't even have one answer...";
         break;
      }
      inter_mono_.Free(); //Free old TextType
      inter_mono_.SetColor(WHITE);
      inter_mono_.SetTextTotal(inter_mono_tmp);
      inter_mono_.SetPosXY(TEXT_MARGINS_X_VAL, TEXT_MARGINS_Y_VAL + i*TEXT_SPACING);
      inter_mono_.RenderTypingAnimationByTime(des, events);
   }

   ScreenEffect::FadeOutScreenOnClick(des, events);

   //Scene 2
   for(int i = 0 ; i < TOTAL_INNER_MONO_SCENE_2 ; ++i)
   {
      switch (i)
      {
      case 0 :
         inter_mono_tmp = "The last thing I remember...";
         break;

      case 1 :
         inter_mono_tmp = "is I, lying on the ground, in the middle of nowhere...";
         break;

      case 2 :
         inter_mono_tmp = "Shimmering star inside my naked eyes.";
         break;

      case 3 :
         inter_mono_tmp = "Skins crawled by the northern's chill.";
         break;

      case 4 :
         inter_mono_tmp = "Metallic taste in my mouth.";
         break;

      case 5 :
         inter_mono_tmp = "Fresh grass's scent tapping my nose.";
         break;

      case 6 :
         inter_mono_tmp = "Winds howling through bare ears.";
         break;

      case 7 :
         inter_mono_tmp = "Loneliness became an everlasting comrade...";
         break;
      }
      inter_mono_.Free();
      inter_mono_.SetColor(WHITE);
      inter_mono_.SetTextTotal(inter_mono_tmp);
      inter_mono_.SetPosXY(TEXT_MARGINS_X_VAL, TEXT_MARGINS_Y_VAL + i*TEXT_SPACING);
      inter_mono_.RenderTypingAnimationByTime(des, events);
   }

   ScreenEffect::FadeOutScreenOnClick(des, events);

   //Scene 3
   for (int i = 0 ; i < TOTAL_INNER_MONO_SCENE_3 ; ++i)
   {
      switch (i)
      {
      case 0 :
         inter_mono_tmp = "There is an old sage, he lives close the Center Continent's border.";
         break;

      case 1 :
         inter_mono_tmp = "Everybody has come to meet him, seeking his wisdom.";
         break;

      case 2 :
         inter_mono_tmp = "I have come too, the old guy looked nice by the way.";
         break;

      case 3 :
         inter_mono_tmp = "but what he said, trembling me...";
         break;

      case 4 :
         inter_mono_tmp = "\"Young man, the answer you seek aren't here, your destiny even I can't predict it.\"";
         break;

      case 5 :
         inter_mono_tmp = "\"Go to the Unname Cave, hidden by the mists on the Forgotten Continent.\"";
         break;

      case 6 :
         inter_mono_tmp = "\"When the moonlight shines down on the sea, the path will open for you.\"";
         break;

      case 7 :
         inter_mono_tmp = "\"And then, the new era for mage will be born, capturing the sky with gods... \"";
         break;
      }
      inter_mono_.Free();
      inter_mono_.SetColor(WHITE);
      inter_mono_.SetTextTotal(inter_mono_tmp);
      inter_mono_.SetPosXY(TEXT_MARGINS_X_VAL, TEXT_MARGINS_Y_VAL + i*TEXT_SPACING);
      inter_mono_.RenderTypingAnimationByTime(des, events);
   }

   ScreenEffect::FadeOutScreenOnClick(des, events);
}
