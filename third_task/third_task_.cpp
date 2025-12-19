#include <iostream>
#include <string>

class Item //아이템을 선언한다
{
//공개적인 곳
public:// 1. 기본 생성자: 매개변수 없이 Item을 만들 때 호출 (이름="", 가격=0 초기화)
	Item()//생성자 선언부
	{
		itemName = "";
		itemPrice = 0; //정수형 멤버변수 itemPrice에 0을 대입
	}//생성자 정의부
	//2. 매개변수가 있는 생성자 : 이름을 설정하며 Item을 만들 때 호출
	Item(std::string name, int price)
	{
		itemName = name;
		itemPrice = price;
	}
	// 3. 소멸자: 메모리에서 Item 객체가 사라질 때 호출
	~Item()//소멸자 선언부
	{
	}//소멸자 정의부
	// 4. Getter 함수: private에 숨겨진 변수 값을 밖에서 읽을 수 있게 함
	std::string GetItemName()
	{
		return itemName;
	}

	int GetItemPrice()
	{
		return itemPrice;
	}
private: //프라이버시를 지켜주세요// 외부에서 함부로 수정하지 못하도록 캡슐화(Encapsulation)
	std::string itemName;//Item 클래스의 문자열형 멤버변수 itemName을 선언한다
	int itemPrice;//Item 클래스의 정수형 멤버변수 itemPrice을 선언한다
};//아이템 정의부

template<typename T>//다양한 타입(Item 외에도 다른 것들)을 담을 수 있게 설계되었습니다.
class Inventory //인벤토리의 선언
{
public:// 생성자: capacity(용량)만큼의 아이템을 저장할 배열을 메모리에 할당
	Inventory(int capacity = 10) //인벤토리 생성자의 선언
	{
		pItems = new Item[capacity];// 동적 배열 생성
		this->capacity = capacity;// 최대 용량 설정
		size = 0;// 현재 들어있는 아이템 개수
	}
	// 소멸자: 가방이 사라질 때 메모리에서 빌린 배열을 다시 돌려줌(delete)
	~Inventory()
	{
		delete[] pItems;
	}
	// 아이템 추가: 가방이 꽉 찼는지 확인 후 아이템을 넣음
	void AddItem(Item item)
	{
		if (size >= capacity)//예외처리// 꽉 찼으면 종료
			return;
		pItems[size++] = item;// 현재 위치에 넣고 size 1 증가
	}
	// 마지막 아이템 삭제: 실제 데이터를 지우기보다 size만 줄여서 접근 불가하게 만듦
	void RemoveLastItem()
	{
		size = size - 1;
	}
	// 전체 출력: 반복문을 돌며 현재 들어있는(size만큼) 아이템 정보 출력
	void PrintAllItems()
	{
		for (int i = 0; i < size; ++i)
		{
			std::cout << "Name : " << pItems[i].GetItemName() << ", Price : " << pItems[i].GetItemPrice() << std::endl;
		}
	}

private:
	T* pItems;// 아이템들을 담을 배열의 주소를 가리키는 포인터
	int capacity;// 최대 수용량
	int size;// 현재 담긴 개수

};  //인벤토리의 정의부

//1.인벤토리 만들기
//2.인벤토리는 아이템을 가지고 있어요

//코드짜기 쉽냐 = item
//코드짜기 어렵냐 = invertory는 item을 관리하기 때문에 어려워요

//프로그래밍 최초에 실행되면 호출되는 함수이다
int main() 
{
	Item item("Hello Item", 1000);//정의해야 사용할 수 있음 //아이템 생성: Item item("Hello Item", 1000); 코드를 통해 이름이 "Hello Item"인 객체가 메모리에 생성됩니다.
	Inventory<Item>inventory; //가방(Inventory) 생성: Inventory<Item> inventory;가 실행되면서 기본 용량(10개)을 가진 동적 배열이 생성됩니다.
	inventory.AddItem(item);//이미 만든 item을 넣습니다.
	inventory.AddItem(Item("Hello Item2", 1100));//Item("Hello Item2", 1100)처럼 즉석에서 생성해서(임시 객체) 넣습니다.

	for (int i = 0; i < 10; ++i)
	{
		inventory.AddItem(Item("Hello Item" + std::to_string(i), 100));
	}//for문을 돌면서 10개를 추가로 넣으려고 시도합니다. (중간에 capacity인 10개가 넘어가면 AddItem 내부의 예외 처리에 의해 더 이상 들어가지 않습니다.)
	
	inventory.RemoveLastItem();//마지막 아이템 제거: RemoveLastItem()이 호출되어 size가 1 줄어듭니다. 가방의 가장 마지막 칸은 이제 없는 것으로 간주됩니다.
	inventory.PrintAllItems();//목록 출력: PrintAllItems()를 통해 현재 가방에 남은 모든 아이템의 이름과 가격을 화면에 보여줍니다.

	//포인터는 껍데기이다
	Item* itemPtr = new Item(); //Item형식을 가진 item 을 생성했습니다, 정의해야 사용가능
	delete itemPtr; //제거//포인터 연습: Item* itemPtr = new Item();을 통해 별도의 아이템을 힙(Heap) 메모리에 만들고 바로 delete로 지웁니다.
	return 0; //프로그램이 종료될 때, 운영체제에 넘겨주는 값입니다.
}//종료: main 함수가 끝나면서 inventory 객체의 소멸자가 호출되고, 내부의 pItems 배열이 메모리에서 해제됩니다