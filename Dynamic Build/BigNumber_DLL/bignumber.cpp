//not using precompiled headers, no need for "stdafx.h"

#include "bignumber.h"

BigNumber::BigNumber()
{
  numbers[0]=0;
  size = 0;
}

BigNumber::BigNumber(long num, int sz)
{
  numbers.resize(sz);
  for (int i = 0; i < sz; i++) 
  {
    numbers[i] = num % 10;
    num /= 10;
  }
  size = sz;
}

BigNumber::BigNumber(const BigNumber& bn)
{
  this->numbers = bn.digits();            
  this->size = bn.getSize();
}

BigNumber::BigNumber(vector<int> nums, int digits)
{
  numbers.clear();
  for(int i=0;i<digits;i++)
  {
    numbers.push_back(nums[i]);
  }
  size = digits;
}

BigNumber BigNumber::operator = (BigNumber const &num)
{
  numbers.clear();
  for(int i=0;i<num.getSize();i++)
  {
    numbers.push_back(num.at(i));
  }
  size = num.getSize();
  return *this;
}

bool BigNumber::operator ==(BigNumber const &num)
{
  if(!(size==num.getSize()))
    return false;
  else
  {
    for(int i=0;i<size;i++)
      if(num.at(i)!=numbers[i])
        return false;
  }
  return true;
}

bool BigNumber::operator > (BigNumber const &num)
{
  if(size<num.getSize())
    return false;
  else if(size>num.getSize())
    return true;
  else
  {
    for(int i=size-1;i>=0;i--)
    {
      if(num.at(i)>numbers[i])
        return false;
      else if(num.at(i)<numbers[i])
        return true;
    }
  }
  return false;
}

bool BigNumber::operator < (BigNumber const &num)
{
  if(size>num.getSize())
    return false;
  else if(size<num.getSize())
    return true;
  else
  {
    for(int i=size-1;i>=0;i--)
    {
      if(num.at(i)<numbers[i])
        return false;
      else if(num.at(i)>numbers[i])
        return true;
    }
  }
  return false;
}

bool BigNumber::operator >= (BigNumber const &num) 
{
  return *this > num || *this == num;
}

bool BigNumber::operator <= (BigNumber const &num) 
{
  return *this < num || *this == num;
}

void BigNumber::print()
{
  for(int i=size-1;i>=0;i--)
  {
    cout << numbers[i];
  }
  cout << endl;
}

int BigNumber::at(int i) const
{
  return numbers[i];
}
 
vector<int> BigNumber::digits() const
{
  return numbers;
}

int BigNumber::getSize() const
{
  return size;
}

int BigNumber::sigDigit()
{
  for (int i = size - 1; i >= 0; i--)
      if (numbers[i] > 0)
          return i;
    return 0;
}

bool BigNumber::set(int value, int index)
{
  int sig = this->sigDigit();
  if (value < 10 && value >= 0 && index >= 0 && index <= sig) 
  {
      numbers[index] = value;
      return true;
  }
  return false;
}

void BigNumber::setVector(vector<int> newval)
{
  this->numbers = newval;
  this->size = newval.size();
}

void BigNumber::setSize(int newsize)
{
  this->size = newsize;
}

BigNumber BigNumber::operator + (BigNumber const &num)
{
  vector<int> added, smallcpy = num.digits(), bigcpy = numbers;
  int carry = 0;

  if((*this)<num)
  {
    bigcpy.swap(smallcpy);
  }

  for(int i=0;i<bigcpy.size()-smallcpy.size()+1;i++)
  {
    smallcpy.push_back(0); //add leading zeroes
  }

  for(int i=0;i<bigcpy.size();i++)
  {
    int val = bigcpy[i] + smallcpy[i] + carry;
    added.push_back(val%10);
    if (val >= 10)
      carry = val / 10;
    else
      carry = 0;
  }
  while(carry>0)
  {
    added.push_back(carry%10);
    carry/=10;
  }
  BigNumber a(added, added.size());
  return a;
}

BigNumber BigNumber::operator - (BigNumber const &num)
{
  vector<int> large = numbers, small = num.digits();
  int biggerSize = size, smallerSize = num.getSize();

  if(numbers==num.digits() || biggerSize < smallerSize) //if this less than num, return 0 (not supporting negatives)
  {
      return BigNumber(0,1);
  }
  while(biggerSize>smallerSize)
  {
    small.push_back(0); //add leading zeroes to make size equal
    smallerSize++;
  }

  int borrow=0, val;
  for (int i = 0; i < biggerSize; i++)
  {
    val = large[i] - borrow - (i>=smallerSize? 0 : small[i]);
    borrow = 0;
    if (val < 0)
    {
      val+=10;
      borrow = 1;
    }
    large[i] = val;
  }
  while(large[biggerSize-1]==0) //remove leading zero
  {
    large.pop_back();
    biggerSize--;
  }
  BigNumber s(large, large.size());
  return s;
}

BigNumber BigNumber::operator * (BigNumber const &num)
{
  vector<int> big = numbers, small = num.digits();
  int bigsz = big.size(), smallsz = small.size();
  vector<int> product(bigsz+smallsz);
  if(bigsz<smallsz)
  {
    big.swap(small);
    bigsz = big.size(), smallsz = small.size();
  }

  for(int i=0;i<bigsz;i++)
  {
    int carry = 0;
    for(int j=0;j<smallsz;j++)
    {
      product[i+j] += carry + small[j] * big[i];
      carry = product[i+j]/10;
      product[i+j] = product[i+j]%10;
    }
    product[i+bigsz]+=carry;
  }
  if(product[product.size()-1]==0) //remove leading zero
  {
    product.pop_back();
  }
  BigNumber p(product, product.size());
  return p;
}

//called when this/num
BigNumber BigNumber::operator / (BigNumber const &num)
{
  try
  {
    vector<int> numer = numbers, denom = num.digits();
    BigNumber nb(numer,numer.size()), db(denom, denom.size());
    
    if(num.getSize()<=1 && num.at(0)==0)
      throw 1;
    else if(*this==num)
      return BigNumber(1,1);
    else if(size<num.getSize())
    { 
      return BigNumber(0,1);
    }
    else if(nb<db)
    {
      return BigNumber(0,1);
    }
    while(nb.getSize()<denom.size())
    {
      numer.push_back(0); //add leading zeroes to make size equal
      nb.setVector(numer);
    }
    //implement division here, guaranteed that n>d

    BigNumber *n = &nb;
    BigNumber q(0,1);
    BigNumber one(1,1);
    while((*n)>=db)
    {
      *n = ((*n)-db);
      q = q+one;
    }
    return q;
  }
  catch(int i)
  {
    cout << "Error: division by 0" << endl;
  }
  /**/
  return BigNumber(0,0);
}

BigNumber BigNumber::operator % (BigNumber const &num)
{
  if(*this<num)
    return BigNumber(0,1);
  BigNumber divd = (*this/num);
  BigNumber rem = divd*num;
  return *this-rem; 
}