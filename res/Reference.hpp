#ifndef RES_REFERENCE_HPP
#define RES_REFERENCE_HPP

namespace res
{
	class Data;
	
	class Reference
	{
		public:
			Reference( const Reference& other );
			Reference( Reference&& other );
			~Reference();
			
			Reference& operator = ( const Reference& other );
			
			Data* operator -> ();
			const Data* operator -> () const;
			operator Data* ();
			operator const Data* () const;
			 
		private:
			Reference( Data* theRes );
			Data* res;
			
			friend class Manager;
	};
}

#endif // RES_REFERENCE_HPP
