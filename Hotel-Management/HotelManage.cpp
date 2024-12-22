#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class Room {
protected:
    int id;
    string typeroom;
    string status;
    string nameguest;
    string guestid;

public:
    virtual void InformationRoom() = 0;
    virtual float RoomCharge() = 0;

    int GetID() {
        return id;
    }

    string GetTypeRoom() {
        return typeroom;
    }

    string GetNameGuest() {
        return nameguest;
    }

    string GetStatus() {
        return status;
    }

    string GetGuestID() {
        return guestid;
    }
    
    void SetID(int id) {
        this->id = id;
    }

    void SetTypeRoom(string typeroom) {
        this->typeroom = typeroom;
    }

    void SetStatus(string status) {
        this->status = status;
    }

    void SetNameGuest(string nameguest) {
        this->nameguest = nameguest;
    }

    void SetGuestID(string guestid) {
        this->guestid = guestid;
    }

    void PrintStatus() {
        cout << id << "\t\t";
        cout << left << typeroom << "\t\t";
        cout << status << "\t\t";
        cout << nameguest << "\t";
    }

    void docFile(ifstream &file){
        file >> id;
        file.ignore();
        getline(file,typeroom,',');
        getline(file,status,',');
        getline(file,nameguest,','); 
        getline(file,guestid,',');        
    }
};

class SingleRoom : public Room {
public:
    float RoomCharge() {
        return (100000);
    }

    void InformationRoom() {
        PrintStatus();
        cout << "\t" <<RoomCharge() <<endl;
    }
};

class DoubleRoom : public Room {
public:
    float RoomCharge() {
        return (120000);
    }

    void InformationRoom() {
        PrintStatus();
        cout << "\t" <<RoomCharge() <<endl;
    }

};

class BusinessRoom : public Room {
public:
    float RoomCharge() {
        return (250000);
    }

    void InformationRoom() {
        PrintStatus();
        cout << "\t" <<RoomCharge() <<endl;
    }

};

class Guest {
    protected:
        string name;
        string phonenum;
        string cmnd;
        string mail;
        string typeguest;
        int renttime;
    
    public:
        virtual void InformationGuest() = 0;
        virtual float discount() = 0;

        void PrintInforGuest() {
            cout << cmnd << "\t\t";
            cout << name << "\t\t";
            cout << phonenum << "\t";
            cout << "\t" << mail << "\t\t";
            cout << typeguest << "\t\t";
            cout << renttime;
        }

        void docFile(ifstream &file){
            getline(file,cmnd,',');
            getline(file,name,',');
            getline(file,phonenum,',');
            getline(file,mail,',');
            getline(file,typeguest,',');
            file >> renttime;
            file.ignore(2);
        }

        void inputinformation(string type){
            typeguest = type;
            cout << "Nhap cmnd: ";
            cin >> cmnd;
            cin.ignore();
            cout << "Nhap ten khach hang: ";
            getline(cin,name);
            
            cout << "Nhap so dien thoai: ";
            getline(cin,phonenum);
            cout << "Nhap mail: ";
            getline(cin,mail);
            cout << "Thoi gian thue phong: ";
            cin>>renttime;
        }

        string GetName() {
            return name;
        }
        string GetPhone() {
            return phonenum;
        }
        string GetID() {
            return cmnd;
        }
        string GetMail() {
            return mail;
        }
        string GetTypeGuest() {
            return typeguest;
        }
        int GetRenttime() {
            return renttime;
        }

};

class RegularGuest : public Guest {
    public:
        float discount(){
            return 1;
        }

        void InformationGuest(){
            PrintInforGuest();
        }
};

class VIPGuest : public Guest {
    public:
        float discount(){
            return 0.8;
        }

        void InformationGuest(){
            PrintInforGuest();
        }
};



class Quanly{
    protected:
        vector<Room*> phong;
        vector<Guest*> khach;
    
    public:
        void InputinformationRoom(){
            ifstream file;
            file.open("room.csv");

            if(file.is_open()){
                int tong,n,m,g;
                file >> tong;
                phong.resize(tong);
                file >> n;
                file >> m;
                file >> g;
                file.ignore();
                for (int i = 0; i < n; i++)
                {
                    phong[i] = new SingleRoom();
                }

                for (int i = n; i < n+m; i++)
                {
                    phong[i] = new DoubleRoom();
                }

                for (int i = n+m; i < n+m+g; i++)
                {
                    phong[i] = new BusinessRoom();
                }

                for(int i=0 ;i<tong ;i++){
                    phong[i]->docFile(file);
                }
                
                file.close();
				cout << "Doc file thanh cong \n";
			    }
			else cout << "\nFile khong mo duoc";
        }

        void outRoom(){
            cout << "====================================== DANH SACH PHONG ======================================" << endl;
			cout << "RoomID\t\tType\t\t\tStatus\t\t\tName\t\tPrice/hour" << endl;
		    for (int i=0; i<phong.size(); i++){
                phong[i] ->InformationRoom();
			}
            cout << "=============================================================================================";
		    cout << "\n\n";
        }


        void SearchRoomByType(string typeroom) {
            bool found = false;
            for (int i = 0; i < phong.size(); i++) {
                if (phong[i]->GetTypeRoom() == typeroom) {
                    phong[i]->InformationRoom();
                    found = true;
                }
            }
            if (!found) {
                cout << "Khong tim thay phong co loai " << typeroom << endl;
            }
        }

        void InputinformationGuest(){
            ifstream file;
            file.open("guest.csv");

            if(file.is_open()){
                int tong,n,m,g;
                file >> tong;
                khach.resize(tong);
                file >> n;
                file >> m;
                file.ignore(2,'\n');
                for (int i = 0; i < n; i++)
                {
                    khach[i] = new RegularGuest();
                }

                for (int i = n; i < n+m; i++)
                {
                    khach[i] = new VIPGuest();
                }

                for(int i=0 ;i<n+m ;i++){
                    khach[i]->docFile(file);
                }
                
                file.close();
				cout << "Doc file thanh cong \n";
			}
			else cout << "\nFile khong mo duoc";
        }

        void outGuest(){
            cout << "==================================================== DANH SACH KHACH HANG ======================================================" << endl;
			cout << "GuestID\t\t\tName\t\tPhone Number\t\tMail\t\t\tType\t\t\tRent-time" << endl;
		    for (int i=0; i<khach.size(); i++){
                khach[i] ->InformationGuest();
                cout << endl;
			}
            cout << "================================================================================================================================";
		    cout << "\n\n";
        }

        void SetRoom(int id){
            phong[id]->SetStatus("unavailable");
            phong[id]->SetNameGuest(khach[khach.size()-1]->GetName());
            phong[id]->SetGuestID(khach[khach.size()-1]->GetID());
        }

        void AddGuest(string typeguest){
            int id;
            Guest* guest;
            if(typeguest == "RegularGuest" ) guest = new RegularGuest();
            else if(typeguest == "VIPGuest") guest = new VIPGuest();
            guest->inputinformation(typeguest);
            khach.insert(khach.end(), guest);
            cout << "Nhap id room khach muon chon: ";
            cin >> id;
            SetRoom(id-1);
        }

        void SetRoomDelete(int id){
            phong[id]->SetStatus("available");
            phong[id]->SetNameGuest(" ");
        }

        void Delete(){
            int k;        
            cout << "Nhap vi tri khach can xoa: ";
            cin >> k;
            int index;
            for(int i=0;i<phong.size();i++){
                if(khach[k-1]->GetID() == phong[i]->GetGuestID()){
                    index = i;
                    break;
                }
            }
            SetRoomDelete(index);
            delete khach[k-1];
            khach.erase(khach.begin() + k-1);
        }

        float ServiceBill(int m) {
            return 10000*khach[m]->GetRenttime();
        }

        float RentBill(int k, int m) {
            float giaphong = phong[k]->RoomCharge();
            float giamgia = khach[m]->discount();
            float tgthue = khach[m]->GetRenttime();
            return giaphong*tgthue*giamgia;         
        }

        float TotalBill(int k, int m) {
            float giadichvu = 10000*khach[m]->GetRenttime();
            float giaphong = phong[k]->RoomCharge();
            float giamgia = khach[m]->discount();
            float tgthue = khach[m]->GetRenttime();
            return giaphong*tgthue*giamgia + giadichvu;
        }

        void XuatBill() {
            cout << "ID khach hang can tinh bill: ";
            string p;
            cin.ignore();
            getline(cin,p);
            int k=-1,m=-1;
            for(int i=0; i < phong.size(); i++) {
                if(phong[i]->GetGuestID() == p) {
                    k = i;
                    break;
                }
            }
            if(k==-1) {
                cout << "Khong tim thay ID khach hang";
                return;
            }
            for(int i=0; i < khach.size(); i++) {
                if(khach[i]->GetID() == p) {
                    m = i;
                    break;
                }
            }
            cout << endl;
            cout << "=============== Hoa don tinh tien ================" << endl;
            cout << "ID phong: \t\t" << phong[k]->GetID() << endl;
            cout << "Ho va ten: \t\t" << khach[m]->GetName() << endl;
            cout << "Loai thanh vien: \t" << khach[m]->GetTypeGuest() << endl;
            cout << "So gio thue: \t\t" << khach[m]->GetRenttime() << endl;
            cout << "Tien thue phong: \t" << fixed << setprecision(0) << RentBill(k,m) << endl;
            cout << "Tien dich vu: \t\t" << fixed << setprecision(0) << ServiceBill(m) << endl; 
            cout << "Tong: \t\t\t" << fixed << setprecision(0) << TotalBill(k,m) << endl;
            cout << "==================================================";
            cout << "\n\n";
        }
        ~Quanly()
        {
            for(int i=0; i<khach.size(); i++)
                delete khach[i];
            for(int i=0; i<phong.size(); i++)
                delete phong[i];
        }
};

class Menu{
	private:
		Quanly ql;
	public:
		void hienThiMenu(){
            int luaChon;
            string type;
            int k;
            do{
                cout << "=============== MENU ===============" << endl;
        		cout << "1. Doc danh sach Phong" << endl;
        		cout << "2. Xuat danh sach Phong" << endl;
                cout << "3. Hien thi loai phong theo yeu cau" <<endl;
                cout << "4. Doc danh sach Khach hang" <<endl;
                cout << "5. Xuat danh sach Khach hang" <<endl;
                cout << "6. Them Khach hang" <<endl;
                cout << "7. Xoa Khach hang theo vi tri" <<endl;
                cout << "8. Xuat bill Khach hang" <<endl;
        		cout << "0. Thoat" << endl;
        		cout << "====================================" << endl;
                cout << "Nhap lua chon cua ban: ";

                cin >> luaChon;
        		switch(luaChon){
                    case 1:
                        ql.InputinformationRoom();
                        break;

                    case 2:
                        ql.outRoom();
                        break;

                    case 3:
                        cout << "Nhap loai phong can tim: ";
                        cin >> type;
                        ql.SearchRoomByType(type);
                        break;

                    case 4:
                        ql.InputinformationGuest();
                        break;
                    
                    case 5:
                        ql.outGuest();
                        break;
                    case 6:
                        cout << "Nhap loai khach can them: ";
                        cin >> type;
                        if(type != "RegularGuest" && type != "VIPGuest"){
                            cout << "khong hop le!!!!!!";
                        }else ql.AddGuest(type);
                        break;

                    case 7:
                        ql.Delete();
                        break;
                    case 8: 
                        ql.XuatBill();
                        break;
                    case 0:
                        cout << "Chuong trinh ket thuc!" << endl;
                        break;


                    default:
                        cout << "Lua chon khong hop le!" << endl;
                        break;
                }
                cout << endl;
            } while(luaChon != 0);
        }
};

int main(){
    system("cls");
    Menu menu;
    menu.hienThiMenu();
    Quanly q;
    q.~Quanly();
}