#ifndef SCENECHANGEEVENT_HPP
#define SCENECHANGEEVENT_HPP

class SceneChangeEvent
{
	public:
		enum Reason : int
		{
			Unspecified = 0,
			// ...
		};
		
		SceneChangeEvent();
		SceneChangeEvent( Reason theReason );
		
		Reason reason;
};

#endif // SCENECHANGEEVENT_HPP
