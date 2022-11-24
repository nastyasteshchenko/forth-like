template<typename T>
class SmartPointer {
public:

    SmartPointer(T *ptr) {
        this->ptr = ptr;
    }

    ~SmartPointer() {
        delete ptr;
    }

    T &operator*() {
        return *ptr;
    }

private:
    T *ptr;
};