#include<cstdio>
class Device{
        // const char * name;
    public:
        // Device(const char * name):name(name){}
        virtual ~Device(){}
        virtual void open() const = 0;
        virtual void read() const = 0;
        virtual void close() const = 0;
};

class LedDevice : public Device{
    public:
        void open() const override{
            std::printf("LedDevice open()\n");
        }
        void read() const override{
            std::printf("LedDevice read()\n");
        }
        void close() const override{
            std::printf("LedDevice close()\n");
        }

};

class BuzzerDevice : public Device{
    public:
        void open() const override{
            std::printf("BuzzerDevice open()\n");
        }
        void read() const override{
            std::printf("BuzzerDevice read()\n");
        }
        void close() const override{
            std::printf("BuzzerDevice close()\n");
        }
};

void run(Device * d){
    d->open();
    d->read();
    d->close();
}

int main(){
    Device * dev[] = {new LedDevice,new BuzzerDevice};
    for(Device * a : dev){
        run(a);
        delete a;
    }
    return 0;
}

