class Game;

template< class SCENE, typename... PARAMS >
typename std::enable_if< std::is_base_of< Scene, SCENE >::value, void >::type
GameBase::changeScenes( const PARAMS&... params )
{
	// Should I use std::forward? I don't know
	SceneChangeEvent tmp;
	nextScene.reset( new SCENE( dynamic_cast< Game& >( * this ), tmp, params... ) );
}

template< class SCENE, typename... PARAMS >
typename std::enable_if< std::is_base_of< Scene, SCENE >::value, void >::type
GameBase::changeScenes( const SceneChangeEvent& event, const PARAMS&... params )
{
	// Should I use std::forward? I don't know
	nextScene.reset( new SCENE( dynamic_cast< Game& >( * this ), event, params... ) );
}
