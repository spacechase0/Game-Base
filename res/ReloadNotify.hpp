#ifndef RES_RELOADNOTIFY_HPP
#define RES_RELOADNOTIFY_HPP

namespace res
{
	class Data;
	
	class ReloadNotify
	{
		public:
			virtual ~ReloadNotify();
			
			virtual void onLoad( const Data& data ) = 0;
	};
}

#endif // RES_RELOADNOTIFY_HPP
