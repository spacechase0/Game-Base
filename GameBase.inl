template< class SCENE, typename... PARAMS >
typename std::enable_if< std::is_base_of< Scene, SCENE >::value, void >::type
GameBase::changeScenes( const PARAMS&... params )
{
	// Should I use std::forward? I don't know
	SceneChangeEvent tmp;
	nextScene.reset( new SCENE( getGame(), tmp, params... ) );
}

template< class SCENE, typename... PARAMS >
typename std::enable_if< std::is_base_of< Scene, SCENE >::value, void >::type
GameBase::changeScenes( const SceneChangeEvent& event, const PARAMS&... params )
{
	// Should I use std::forward? I don't know
	nextScene.reset( new SCENE( getGame(), event, params... ) );
}
