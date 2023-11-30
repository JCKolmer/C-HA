#include "vector.h"

#include <iterator>
#include <math.h>
#include <iostream>


namespace linalg {
auto operator<<(std::ostream& ostr, const Vector& x) -> std::ostream& {
    ostr << "[ ";
    std::copy(x.begin(), x.end(), std::ostream_iterator<float>(ostr, " "));
    ostr << "]";
    return ostr;
}

    Vector::Vector(std::size_t n) :
        data_{std::vector<float> (n)} {
           // iterator{data_.begin()};
           // const_iterator{data_.begin()};
            }
    
    Vector::Vector(std::size_t n, float val) : 
        data_{std::vector<float> (n,val)} {
           // iterator{data_.begin()};
           // const_iterator{data_.begin()};
        }

    Vector::Vector(std::initializer_list<float> list) :
        data_{std::vector<float> (list)} {
           // iterator{data_.begin()};
           // const_iterator{data_.begin()};
        }
    
    Vector& Vector::operator=(float val)
    {
        std::size_t n = data_.size();
        data_ = std::vector<float> (n,val);
        return *this;
    }

    void Vector::assign(float val)
    {
        std::size_t n = data_.size();
        data_ = std::vector<float> (n,val);
    }

    void Vector::assign(Vector v)
    {
        data_ = v.data_;
    }

    std::size_t Vector::size() const
    {
        return data_.size();
    }

    Vector::iterator Vector::begin()
    {
        return data_.begin();
    }

    Vector::iterator Vector::end()
    {
        return data_.end();
    }

    Vector::const_iterator Vector::begin() const
    {
        return data_.begin();
    }

    Vector::const_iterator Vector::end() const
    {
        return data_.end();
    }

    Vector::const_iterator Vector::cbegin() const
    {
        return data_.begin();
    }

    Vector::const_iterator Vector::cend() const
    {
        return data_.end();
    }

    float& Vector::operator[](int idx) {
        if(idx<0)
        {
            return data_[data_.size()+idx];
        }
        else
        {
            return data_[idx];
        }
    }

    const float& Vector::operator[](int idx) const
    {
         if(idx<0)
        {
            return data_[data_.size()+idx];
        }
        else
        {
            return data_[idx];
        }
    }

    float& Vector::coeff(int idx)
    {
        if(idx<0)
        {
            throw std::out_of_range("id out of range");
        }
        if(idx>(data_.size()-1))
        {
            throw std::out_of_range("id out of range");
        }
        return data_[idx];
    }

    const float& Vector::coeff(int idx) const
    {
        if(idx<0)
        {
            throw std::out_of_range("id out of range");
        }
        if(idx>(data_.size()-1))
        {
            throw std::out_of_range("id out of range");
        }
        return data_[idx];
    }

    Vector& Vector::operator+=(float val)
    {
       for(int i=0; i<data_.size(); i++)
        {
            data_[i] = data_[i] + val;
        }
        return *this;
    }

    Vector& Vector::operator-=(float val)
    {
        for(int i=0; i<data_.size(); i++)
        {
            data_[i] = data_[i] - val;
        }
        return *this;
    }

    Vector& Vector::operator*=(float val){
        for(int i=0; i<data_.size(); i++)
        {
            data_[i] = data_[i] * val;
        }
        return *this;
    }

    Vector& Vector::operator/=(float val){
         for(int i=0; i<data_.size(); i++)
        {
            data_[i] = data_[i] / val;
        }
        return *this;
    }

    Vector& Vector::operator+=(const Vector &y)
    {
        if(y.size() != data_.size())
        {
            throw std::invalid_argument("Vector is not from the same size");
        }
        for(int i = 0; i<y.size();i++)
        {
            data_[i] = y[i] + data_[i];
        }
        return *this;
    }

    Vector& Vector::operator-=(const Vector &y)
    {
        if(y.size() != data_.size())
        {
            throw std::invalid_argument("Vector is not from the same size");
        }
        for(int i = 0; i<y.size();i++)
        {
            data_[i] = data_[i] - y.operator[](i);
        }
        return *this;
    };

float min(const Vector &x)
{
    if(x.size() == 0)
    {
        throw std::invalid_argument("Vector is empty");
    }
    float min = x[1];
    for (float f : x)
    {
        if (f<min)
        {
            min = f;
        }
    }
    return min;
} 

float max(const Vector &x)
{
    if(x.size() == 0)
    {
        throw std::invalid_argument("Vector is empty");
    }
    float max = x[1];
    for (float f : x)
    {
        if (f>max)
        {
            max = f;
        }
    }
    return max;
} 

std::size_t argmin(const Vector &x)
{
    if(x.size() == 0)
    {
        throw std::invalid_argument("Vector is empty");
    }
    float min = x[1];
    std::size_t minimalIndex = 0;
    for (int i = 0; i<x.size(); i++)
    {
        if (x[i]<min)
        {
            min = x[i];
            minimalIndex = i;
        }
    }
    return minimalIndex;
}

std::size_t argmax(const Vector &x)
{
    if(x.size() == 0)
    {
        throw std::invalid_argument("Vector is empty");
    }
    float max = x[1];
    std::size_t maximalIndex = 0;
    for (int i = 0; i<x.size(); i++)
    {
        if (x[i]<max)
        {
            max = x[i];
            maximalIndex = i;
        }
    }
    return maximalIndex;
}

std::size_t non_zeros(const Vector &x)
{
    std::size_t anz = 0;
    for(int i = 0; i<x.size(); i++)
    {
        if(x[i] != 0)
        {
            anz++;
        }
    }
    return anz;
}

float sum(const Vector &x) {
    float sum = 0;
    for(float f : x)
    {
        sum = sum + f;
    }
    return sum;
}

float prod(const Vector &x) {
    float prod = 0;
    for(float f : x)
    {
        prod = prod * f;
    }
    return prod;
}

float dot(const Vector &x, const Vector &y)
{
    if(y.size() != x.size())
    {
        throw std::invalid_argument("Vector is not from the same size");
    }
    float sum = 0;
    for(int i = 0; i<x.size(); i++)
    {
        sum = sum + (x[i]*y[i]);
    }
    return sum;
}

float norm(const Vector &x) {
    float sum = 0;
    for(int i = 0; i<x.size(); i++)
    {
        sum = sum + (x[i]*x[i]);
    }
    return std::sqrt(sum);
}

void normalize(Vector &x)
{
    x /= norm(x);
}

Vector normalized(const Vector &x)
{
    Vector erg = Vector(x);
    linalg::Vector::iterator iterator1 = erg.begin();
    for(int i = 0; i<erg.size(); i++)
    {
        float var = x[i] / norm(x);
        erg[i] = var;
    }
    return erg;
}

Vector floor(const Vector &x) {
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    for (int i = 0; i<x.size(); i++)
    {
        erg[i] = std::floor(x[i]);
    }
    return erg;
}

Vector ceil(const Vector &x)
{
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    for (int i = 0; i<x.size(); i++)
    {
        erg[i] = std::ceil(x[i]);
    }
    return erg;
}

Vector operator+(const Vector &x)
{
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    return x;
}

Vector operator-(const Vector &x)
{
    Vector erg = Vector(x.size(),0);
    for(int i = 0; i<x.size(); i++)
    {
        erg[i] = -x[i];
    }
    return erg;
}

Vector operator+(const Vector &x, const Vector &y) {
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    erg.operator+=(y);
    return erg;
}

Vector operator-(const Vector &x, const Vector &y) {
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    erg.operator-=(y);
    return erg;
}

Vector operator+(const Vector &x, float val) {
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    erg.operator+=(val);
    return erg;
}

Vector operator-(const Vector &x, float val) {
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    erg.operator-=(val);
    return erg;
}

Vector operator*(const Vector &x, float val) {
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    erg.operator*=(val);
    return erg;
}

Vector operator/(const Vector &x, float val) {
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    erg.operator/=(val);
    return erg;
}

Vector operator+(float val, const Vector &x) {
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    erg.operator+=(val);
    return erg;
}

Vector operator-(float val, const Vector &x) {
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    erg.operator-=(val);
    return erg;
}

Vector operator*(float val, const Vector &x){
    Vector erg = Vector(x.size(),0);
    erg.assign(x);
    erg.operator*=(val);
    return erg; 
}

}

/*
 * Please Implement all functions from the header file here!#
 * Have fun! :-) And don't forget maybe you can use standard algorithms ;-)
 */
