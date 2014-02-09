class Game;

template< class SCENE, typename... PARAMS >
typename std::enable_if< std::is_base_of< Scene, SCENE >::value, void >::type
GameBase::changeScenes( PARAMS&... params )
{
	// Should I use std::forward? I don't know
	SceneChangeEvent tmp;
	nextScene.reset( new SCENE( dynamic_cast< Game& >( * this ), tmp, params... ) );
}

template< class SCENE, typename... PARAMS >
typename std::enable_if< std::is_base_of< Scene, SCENE >::value, void >::type
GameBase::changeScenes( SceneChangeEvent& event, PARAMS&... params )
{
	// Should I use std::forward? I don't know
	nextScene.reset( new SCENE( dynamic_cast< Game& >( * this ), event, params... ) );
}
