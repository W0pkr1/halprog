#include<vector>
#include<algorithm>
#include<cmath>
namespace pl{
    template<typename T>
    auto resizer(T & first_polinom, T& second_polinom, bool no_exeption){
        if(first_polinom.size() < second_polinom.size()){
            first_polinom.resize(second_polinom.size());
        }

        else if(second_polinom.size() < first_polinom.size() && no_exeption)
		{
                second_polinom.resize(first_polinom.size());
        }
    }


    template<typename T,typename R, typename F>
    auto transform_polinom(T & first_polinom, R second_polinom, F fun){
    	resizer(first_polinom,second_polinom, true);

    	for(int i = 0;i<first_polinom.size();++i){
			first_polinom[i] = fun(first_polinom[i],second_polinom[i]);
			}
		}


    auto add = [](auto & x, auto & y){ return x + y; };
    auto sub = [](auto & x, auto & y){ return x - y; };

}


template<typename T>
class polinom{
    std::vector<T> data;

    public: polinom( std::vector<T> d): data(d) {}


    polinom() = default;
	polinom( polinom const& ) = default;
	polinom( polinom && ) = default;

    polinom<T>& operator=(polinom const&) = default;
	polinom<T>& operator=(polinom &&) = default;


	T& operator[]( int i ) { return data[i]; }
	T const& operator[]( int i ) const { return data[i]; }


    polinom<T>& operator+= (polinom<T>& cpy)
	{
		pl::transform_polinom(*this,cpy,pl::add);
	    return *this;
	}

    polinom<T>& operator-= (polinom<T> & cpy)
	{
		pl::transform_polinom(*this,cpy,pl::sub);
		return *this;
	}

    polinom<T>& operator*= (T const& scl)
	{
    	for(auto e:data)
		{
			e *= scl;
		}

		return *this;
	}

    polinom<T>& operator/= (T const& scl)
	{
		for(auto e:data)
		{
			e /= scl;
		}
		return *this;
    }

    int size()const
	{
		return static_cast<int>( data.size() );
	}
		auto begin()
	{
		return data.begin();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}

	auto end()
	{
		return data.end();
	}

	auto cend() const
	{
		return data.cend();
	}

    auto resize(int new_size)
    {
        return data.resize(new_size);
    }

	auto pop_back()
	{
		data.pop_back();
	}

	auto push_back(T value)
	{
		data.push_back(value);
	}
};
//összeadás

template<typename T,typename R>
polinom<T> operator+(polinom<T>const& egy, polinom<R>const& ketto)
{
	auto result = egy;
	auto ketto_copy=ketto;
	pl::resizer(result,ketto_copy,false);

	for(int i = 0; i < ketto.size();++i)
	{
		result[i] += ketto_copy[i];
	}
	return result;
}


template<typename T,typename R>
polinom<T>&& operator+(polinom<T>&& egy, polinom<R>const& ketto)
{
	pl::resizer(egy,ketto, false);
	for(int i=0;i<ketto.size();++i)
	{
		egy[i]+=ketto[i];
	}
	return std::move(egy);

}


template<typename T,typename R>
polinom<T>&& operator+(polinom<T>const& egy, polinom<R>&& ketto)
{
	pl::resizer(ketto,egy,false);
	for(int i=0;i<egy.size();++i)
	{
		ketto[i]+=egy[i];
	}
	return std::move(ketto);
}


template<typename T,typename R>
polinom<T>&& operator+(polinom<T>&& egy, polinom<R>&& ketto)
{
	pl::resizer(egy,ketto,true);
	for(int i=0;i<ketto.size();++i)
	{
		egy[i]+=ketto[i];
	}
	return std::move(egy);
}


// Kivonás

template<typename T,typename R>
polinom<T> operator-(polinom<T>const& egy, polinom<R>const& ketto)
{
	auto result = egy;
	auto ketto_copy=ketto;
	pl::resizer(result,ketto_copy,false);

	for(int i = 0; i < ketto.size();++i)
	{
		result[i] -= ketto_copy[i];
	}
	return result;
}


template<typename T,typename R>
polinom<T>&& operator-(polinom<T>&& egy, polinom<R>const& ketto)
{
	pl::resizer(egy,ketto, false);
	for(int i=0;i<ketto.size();++i)
	{
		egy[i]-=ketto[i];
	}
	return std::move(egy);

}


template<typename T,typename R>
polinom<T>&& operator-(polinom<T>const& egy, polinom<R>&& ketto)
{
	pl::resizer(ketto,egy,false);
	for(int i=0;i<egy.size();++i)
	{
		ketto[i]-=egy[i];
	}
	return std::move(ketto);
}


template<typename T,typename R>
polinom<T>&& operator-(polinom<T>&& egy, polinom<R>&& ketto)
{
	pl::resizer(egy,ketto,true);
	for(int i=0;i<ketto.size();++i)
	{
		egy[i]-=ketto[i];
	}
	return std::move(egy);
}

//szorzás

template<typename T>
polinom<T> operator*(polinom<T> const& first_polinom, polinom<T> const& second_polinom)
{
	auto copy = first_polinom;
	auto result = first_polinom;
	result.resize(first_polinom.size() + second_polinom.size() -1);

	for(auto e:result){e=0;}
	for(int i = 0; i < copy.size();++i){
		for(int j = 0;j < second_polinom.size();++j){
			result[i+j] += first_polinom[i]*second_polinom[j];
		}
	}
	return result;
}


template<typename T>
polinom<T>&& operator*(polinom<T> const& first_polinom, polinom<T>&& second_polinom)
{
	auto copy = first_polinom;
	first_polinom.resize(first_polinom.size() + second_polinom.size() -1);

	for(auto e:first_polinom){e=0;}
	for(int i = 0; i < copy.size();++i){
		for(int j = 0;j < second_polinom.size();++j){
			first_polinom[i+j] += first_polinom[i]*second_polinom[j];
		}
	}
	return std::move(first_polinom);
}


template<typename T>
polinom<T>&& operator*(polinom<T> && first_polinom, polinom<T> const& second_polinom)
{
	auto copy = first_polinom;
	first_polinom.resize(first_polinom.size() + second_polinom.size() -1);

	for(auto e:first_polinom){e=0;}
	for(int i = 0; i < copy.size();++i){
		for(int j = 0;j < second_polinom.size();++j){
			first_polinom[i+j] += first_polinom[i]*second_polinom[j];
		}
	}
	return std::move(first_polinom);
}


template<typename T>
polinom<T>&& operator*(polinom<T>&& first_polinom, polinom<T>&& second_polinom)
{
	auto copy = first_polinom;
	first_polinom.resize(first_polinom.size() + second_polinom.size() -1);

	for(auto e:first_polinom){e=0;}
	for(int i = 0; i < copy.size();++i){
		for(int j = 0;j < second_polinom.size();++j){
			first_polinom[i+j] += first_polinom[i]*second_polinom[j];
		}
	}
	return std::move(first_polinom);
}


//deriválás
template<typename T>
auto derrivate_once(polinom<T>& poli)
{
	for (int i = 0; i < poli.size()-1; ++i)
		{
			poli[i] = poli[i+1] *(i+1);
		}
	poli.pop_back();
}


template<typename T>
auto derrivate_more(polinom<T> poli, int number_of_derrivations)
{
	for (int derrivations = 0; derrivations < number_of_derrivations; derrivations++)
	{
		if(poli.size()  == 0){
			std::cout<<" After "<<derrivations<<" derrivations this polinom is zero"<<std::endl;
			break;
		}
		derrivate_once(poli);
	}
	return poli;
}

//integrálás
template<typename T>
auto calculate_integral(polinom<T>& poli)
{
    poli.push_back(0);
	for (int i = 0; i < poli.size(); ++i)
	{
		poli[poli.size()-i-1] = poli[poli.size()-i-2]/(poli.size()-i-2);
	}
	poli[0] = 0;
}

template<typename T>
auto integrate(polinom<T> poli, T min_point, T max_point)
{
	calculate_integral(poli);
	T max_value = 0;
	T min_value = 0;
	for (int i = 0; i < poli.size(); ++i)
	{
		max_value += poli[i]*pow(max_point,i);
		min_value += poli[i]*pow(min_point,i);
	}
	return max_value-min_value;
}



