template<typename T>
void Column_spec<T>::ls(const uint ind) const
  {
    cout<<"  "<< data[ind] <<"  ";
  }

template<typename T>
void Column_spec<T>::Write(FILE *&, const uint ind) const {}


