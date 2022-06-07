#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>
#include <chrono>
#include <cstring>
#include <list>


template <class T>
class IDynamicArray
{
	public:
	
	virtual int size ( void ) = 0;
	virtual void add ( T item ) = 0;
	virtual void add ( T item , int index ) = 0;
	virtual T remove(int index) = 0;
	virtual T get( int pos ) = 0;
	virtual int resize( void ) = 0;
	
	virtual ~IDynamicArray(){}
	
};

template <class T>
class TesterArray 
{
	std::unique_ptr< IDynamicArray<T> > itests;
	int num = 0;
	public:	
	
	TesterArray( std::unique_ptr< IDynamicArray<T> > _itests , int _num ) : itests( std::move( _itests ) ) , num( _num ) {}
	~TesterArray(){}
	
	void RunTestsAdd( void )
	{
		for( int i = 0; i < num ; i++ )
		{
			itests->add( i );		
		}		
	}
	
	void RunTestsGet( void )
	{
		for( int i = 0; i < num ; i++ )
		{
			std::cout<<" "<<itests->get( i );		
		}		
		std::cout<<std::endl;
	}
	
	void RunTestsRemove( void )
	{
		for( int i = 0; i < 10 ; i++ )
		{
			std::cout<<" remove "<< i + 5;
			itests->remove( i + 5 );		
		}		
		std::cout<<std::endl;
	}
};



template <class T>
class SingleArray : public IDynamicArray<T>
{
	T* arr;
	
	int length = 0;
	int capacity = 0;
	public:
	
	SingleArray( int _size = 0 ) : length( _size ) { arr = new T[length]; }
	~SingleArray() override { delete[] arr; } 
	
	SingleArray& operator=( const SingleArray& ) = delete;
	SingleArray& operator=( const SingleArray&& ) = delete;
	SingleArray ( const SingleArray&& ) = delete;
	
	int size ( void ) override
	{
		return capacity;
	}
	
	void add ( T item ) override
	{
		capacity++;
		
		if( capacity > length )
		{
			length = resize();
			
			std::cout<<"resize , size = " << length << std::endl;
		}
		
		arr[ capacity -1 ] = item;				
	}
	
	void add ( T item , int index ) override
	{
		if( index <= length )
		{		
			arr[ index ] = item;	
		}			
	}
	
	T remove(int index) override
	{
		if( index > capacity ) return 1;
		
		T item = arr[ index ];		
		
		capacity--;
		
		T* newarr = new T [ length ];
		
		memcpy( newarr , arr , index * sizeof( T ) );		
		
		memcpy( &newarr[ index ] , &arr[ index + 1 ] , ( length - index ) * sizeof( T ) );
		
		delete[] arr;	
		
		arr = newarr;
		
		return item;		
	}
	
	T get( int pos ) override
	{
		return arr[ pos ];
	}
	
	int resize( void ) override
	{
		int new_size = length + 1;
		
		T* new_arr = new T[ new_size ];
		
		std::memcpy( new_arr , arr , length * sizeof( T ) );
		
		delete[] arr;		
		
		arr = new_arr;			
		
		return new_size;
	}

};

template <class T>
class VectorArray : public IDynamicArray<T>
{
	T* arr;
	
	int vector;
	
	int length = 0;
	int capacity = 0;
	public:
	
	VectorArray( int _vector = 2 , int _size = 0 ) : vector( _vector ) , length( _size ) { arr = new T[length]; }
	~VectorArray() override { delete[] arr; } 
	
	VectorArray& operator=( const VectorArray& ) = delete;
	VectorArray& operator=( const VectorArray&& ) = delete;
	VectorArray ( const VectorArray&& ) = delete;
	
	int size ( void ) override
	{
		return capacity;
	}
	
	void add ( T item ) override
	{
		capacity++;
		
		if( capacity > length )
		{
			length = resize();
			
			std::cout<<"resize , size = " << length << std::endl;
		}
		
		arr[ capacity -1 ] = item;				
	}
	
	void add ( T item , int index ) override
	{
		if( index <= length )
		{		
			arr[ index ] = item;	
		}			
	}
	
	T remove(int index) override
	{
		if( index > capacity ) return 1;
		
		T item = arr[ index ];		
		
		capacity--;
		
		T* newarr = new T [ length ];
		
		memcpy( newarr , arr , index * sizeof( T ) );		
		
		memcpy( &newarr[ index ] , &arr[ index + 1 ] , ( length - index ) * sizeof( T ) );
		
		delete[] arr;	
		
		arr = newarr;
		
		return item;		
	}
	
	T get( int pos ) override
	{
		return arr[ pos ];
	}
	
	int resize( void ) override
	{
		int new_size = length + vector;
		
		T* new_arr = new T[ new_size ];
		
		std::memcpy( new_arr , arr , length * sizeof( T ) );
		
		delete[] arr;		
		
		arr = new_arr;			
		
		return new_size;
	}

};

template <class T>
class FactorArray : public IDynamicArray<T>
{
	T* arr;
	
	int factor;
	
	int length = 0;
	int capacity = 0;
	public:
	
	FactorArray( int _factor = 2 , int _size = 1 ) : factor( _factor ) , length( _size ) { arr = new T[length]; }
	~FactorArray() override { delete[] arr; } 
	
	FactorArray& operator=( const FactorArray& ) = delete;
	FactorArray& operator=( const FactorArray&& ) = delete;
	FactorArray ( const FactorArray&& ) = delete;
	
	int size ( void ) override
	{
		return capacity;
	}
	
	void add ( T item ) override
	{
		capacity++;
		
		if( capacity > length )
		{
			length = resize();
			
			std::cout<<"resize , size = " << length << std::endl;
		}
		
		arr[ capacity -1 ] = item;				
	}
	
	void add ( T item , int index ) override
	{
		if( index <= length )
		{		
			arr[ index ] = item;	
		}			
	}
	
	T remove(int index) override
	{
		if( index > capacity ) return 1;
		
		T item = arr[ index ];		
		
		capacity--;
		
		T* newarr = new T [ length ];
		
		memcpy( newarr , arr , index * sizeof( T ) );		
		
		memcpy( &newarr[ index ] , &arr[ index + 1 ] , ( length - index ) * sizeof( T ) );
		
		delete[] arr;	
		
		arr = newarr;
		
		return item;		
	}
	
	T get( int pos ) override
	{
		return arr[ pos ];
	}
	
	int resize( void ) override
	{
		int new_size = length * factor;
		
		T* new_arr = new T[ new_size ];
		
		std::memcpy( new_arr , arr , length * sizeof( T ) );
		
		delete[] arr;		
		
		arr = new_arr;			
		
		return new_size;
	}

};

template <class T>
class MatrixArray : public IDynamicArray<T>
{
	T** arr;
	
	int factor;
	
	int length = 0;
	int capacity = 0;
	public:
	
	MatrixArray( int _factor = 2 , int _size = 1 ) : factor( _factor ) , length( _size ) 
	{
	 	arr = new T*[length]; 
	 	for( int i = 0; i < length; i++ )
	 	{
	 		arr[ i ] = new T[ 1 ];
	 	}
	 }
	~MatrixArray() override { delete[] arr; } 
	
	MatrixArray& operator=( const MatrixArray& ) = delete;
	MatrixArray& operator=( const MatrixArray&& ) = delete;
	MatrixArray ( const MatrixArray&& ) = delete;
	
	int size ( void ) override
	{
		return capacity;
	}
	
	void add ( T item ) override
	{
		capacity++;
		
		if( capacity > length )
		{
			length = resize();
			
			std::cout<<"resize , size = " << length << std::endl;
		}
		
		arr[ capacity -1 ][0] = item;				
	}
	
	void add ( T item , int index ) override
	{
		if( index <= length )
		{		
			arr[ index ][0] = item;	
		}			
	}
	
	T remove(int index) override
	{
		if( index > capacity ) return 1;
		
		T item = arr[ index ][1];		
		
		capacity--;
		
		T** new_arr = new T*[ length ];
		for( int i = 0; i < length; i++ )
	 	{
	 		new_arr[ i ] = new T[ 1 ];
	 	}
		
		for( int i = 0; i < index; i++ )
		{
     			for( int j =0 ; j < 1; j++ )
     			{
       			new_arr[ i ][ j ] = arr[ i][ j ];
       		}
       	}
       	
       	for( int i = index; i < length-1; i++ )
		{
     			for( int j =0 ; j < 1; j++ )
     			{
       			new_arr[ i ][ j ] =arr[ i + 1 ][ j ];
       		}
       	}
		
		for(int i = 0; i < length; ++i)
    			delete[] arr[i];
		delete[] arr;		
		
		arr = new_arr;
		
		return item;		
	}
	
	T get( int pos ) override
	{
		return arr[ pos ][ 0 ];
	}
	
	int resize( void ) override
	{
		int new_size = length * factor;
		
		T** new_arr = new T* [ new_size ];
		for( int i = 0; i < new_size; i++ )
	 	{
	 		new_arr[ i ] = new T[ 1 ];
	 	}
		
		
		for( int i = 0; i < length; i++ )
		{
     			for( int j =0 ; j < 1; j++ )
     			{
       			new_arr[ i ][ j ] = arr[ i ][ j ];
       		}
       	}
		
		for(int i = 0; i < length; ++i)
    			delete[] arr[i];
		delete[] arr;		
		
		arr = new_arr;			
		
		return new_size;
	}

};

template <class T>
class ArrayList : public IDynamicArray<T>
{
	std::list<T> arr;	
	
	public:
	
	ArrayList() { }
	~ArrayList() override { } 
	
	ArrayList& operator=( const ArrayList& ) = delete;
	ArrayList& operator=( const ArrayList&& ) = delete;
	ArrayList ( const ArrayList&& ) = delete;
	
	int size ( void ) override
	{
		return arr.size();
	}
	void add ( T item ) override
	{
		arr.push_back( item );				
	}
	void add ( T item , int index ) override
	{	
		if( index < arr.size() )
		{
			auto it = arr.begin();
			
			for( int i = 0; i < index; i++ ) it++;
		
			arr.insert( it , item );
		}
	}
	T remove(int index) override
	{
		T data = 0;
		
		if( index < arr.size() )
		{
			auto it = arr.begin();	
		
			data = *it;
			
			for( int i = 0; i < index; i++ ) it++;
			
			arr.erase( it );		
		}
			
		return data;
	}
	T get( int index ) override
	{
		T data = 0;
		
		if( index < arr.size() )
		{
			auto it = arr.begin();	
			
			for( int i = 0; i < index; i++ ) it++;
			
			data = *( it );
		}
			
		return data;
	}
	int resize( void ) override
	{
		return 0;
	}
};


struct TestData
{
	int elements;
	double time;
};

int main ( int argc , char** argv )
{
	std::cout<<"algo5"<<std::endl;
	
	std::vector<TestData> SArray(0);
	std::vector<TestData> VArray(0);
	std::vector<TestData> FArray(0);
	std::vector<TestData> MArray(0);
	std::vector<TestData> LArray(0);
	
	try
	{		
		#define EXP3 1
		#if EXP3
		{
			TesterArray<int> tester( std::make_unique<SingleArray<int>>( 10 ) , 200 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 200;
       		td.time = diff.count();
       		
       		SArray.push_back( td );
		}
		#endif
		
		#define EXP4 1
		#if EXP4
		{
			TesterArray<int> tester( std::make_unique<VectorArray<int>>( 2 , 10 ) , 200 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 200;
       		td.time = diff.count();
       		
       		VArray.push_back( td );
		}
		#endif
		
		#define EXP5 1
		#if EXP5
		{
			TesterArray<int> tester( std::make_unique<FactorArray<int>>( 2 , 10 ) , 200 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 200;
       		td.time = diff.count();
       		
       		FArray.push_back( td );
		}
		#endif
		
		#define EXP6 1
		#if EXP6
		{
			TesterArray<int> tester( std::make_unique<MatrixArray<int>>( 2 , 10 ) , 200 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
						
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 200;
       		td.time = diff.count();
       		
       		MArray.push_back( td );
		}
		#endif
		
		#define EXP7 1
		#if EXP7
		{
			TesterArray<int> tester( std::make_unique<SingleArray<int>>( 10 ) , 400 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 400;
       		td.time = diff.count();
       		
       		SArray.push_back( td );
		}
		#endif
		
		#define EXP8 1
		#if EXP8
		{
			TesterArray<int> tester( std::make_unique<VectorArray<int>>( 2 , 10 ) , 400 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 400;
       		td.time = diff.count();
       		
       		VArray.push_back( td );
		}
		#endif
		
		#define EXP9 1
		#if EXP9
		{
			TesterArray<int> tester( std::make_unique<FactorArray<int>>( 2 , 10 ) , 400 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 400;
       		td.time = diff.count();
       		
       		FArray.push_back( td );
		}
		#endif
		
		#define EXP10 1
		#if EXP10
		{
			TesterArray<int> tester( std::make_unique<MatrixArray<int>>( 2 , 10 ) , 400 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
						
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 400;
       		td.time = diff.count();
       		
       		MArray.push_back( td );
       	}
		#endif
		
		#define EXP11 1
		#if EXP11
		{
			TesterArray<int> tester( std::make_unique<ArrayList<int>>( ) , 200 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
						
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 200;
       		td.time = diff.count();
       		
       		LArray.push_back( td );       		
		}
		#endif
		
		#define EXP12 1
		#if EXP12
		{
			TesterArray<int> tester( std::make_unique<ArrayList<int>>( ) , 400 );
			
			auto start = std::chrono::system_clock::now();
			tester.RunTestsAdd();
			
			tester.RunTestsGet();
						
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;	
       		
       		TestData td;
       		
       		td.elements = 400;
       		td.time = diff.count();
       		
       		LArray.push_back( td );       		
		}
		#endif
		
		
		for( auto a : SArray )
		{
			std::cout << "SingleArray  : elements : " << a.elements << " : time left : " << a.time << " s\n";
		}
		for( auto a : VArray )
		{
			std::cout << "VectorArray  : elements : " << a.elements << " : time left : " << a.time << " s\n";
		}
		for( auto a : FArray )
		{
			std::cout << "FactoryArray : elements : " << a.elements << " : time left : " << a.time << " s\n";
		}
		for( auto a : MArray )
		{
			std::cout << "MatrixArray  : elements : " << a.elements << " : time left : " << a.time << " s\n";
		}
		for( auto a : LArray )
		{
			std::cout << "ArrayList    : elements : " << a.elements << " : time left : " << a.time << " s\n";
		}
		
		
	}
	catch( ... )
	{
		std::cout<<"error"<<std::endl;
	}
	
	

	return 0;
}





