#include <iostream>
#include <fstream>
using namespace std;
struct inventory_item
{
	char name[20];
	int item_ID;
	char category[20];
	int item_count;
    char allocated_to[20][20];
};

void AddInventoryItem(inventory_item it)
{
    
	cout << "Enter name of the item "<<endl;
	cin >> it.name;
	cout << "Enter the ID of the item "<<endl;
	cin >> it.item_ID;
	cout << "Enter the category of the item "<<endl;
	cin >> it.category;
	cout << "Enter the count of the item "<<endl;
	cin >> it.item_count;
	
    fstream inventory("Inventory.txt", ios::out | ios::binary |ios::app);
    
    inventory.write(reinterpret_cast<char *>(&it),sizeof(it)); 
    
	inventory.close();
}
 void ViewAllInventoryItem(inventory_item it)
 {
		fstream inventory("Inventory.txt", ios::in | ios::binary);
		inventory.read(reinterpret_cast<char *>(&it),sizeof(it)); 
		while (!inventory.eof()) 
			{ 
 				cout << "NAME: "; 
 				cout << it.name << endl; 	
 				cout << "ITEM ID: "; 
 				cout << it.item_ID << endl; 
 				cout << "CATEGORY: "; 
 				cout << it.category << endl; 
 				cout << "ITEM COUNT: "; 
 				cout << it.item_count << endl << endl ; 
 				inventory.read(reinterpret_cast<char *>(&it),sizeof(it));
            }
 	
 }
 
 void SearchInventoryItem (inventory_item it)
  {		
  
        fstream inventory("Inventory.txt", ios::in | ios::binary);
        inventory.read(reinterpret_cast<char *>(&it),sizeof(it)); 
        int id;
        cout << "Enter ID of the item you wanna search!!! " << endl;
        cin >> id ;
		
		while (!inventory.eof()) 
			{ 
 				if(id==it.item_ID)
 				{
 				cout << "NAME: "; 
 				cout << it.name << endl; 	
 				cout << "ITEM ID: "; 
 				cout << it.item_ID << endl; 
 				cout << "CATEGORY: "; 
 				cout << it.category << endl; 
 				cout << "ITEM COUNT: "; 
 				cout << it.item_count << endl << endl ;
				}
				inventory.read(reinterpret_cast<char *>(&it),sizeof(it)); 
            }
 	
 }
 
 void EditInventoryItem(inventory_item it)
 {
 	fstream inventory("Inventory.txt", ios::in | ios::binary|ios::out);
        inventory.read(reinterpret_cast<char *>(&it),sizeof(it)); 
        int id;
        bool flag = 0;
        cout << "Enter ID of the item you wanna edit!!! " << endl;
        cin >> id ;
		
		 while (!inventory.eof()) 
			{ 
 				if(id==it.item_ID)
 				{
 				cout << "NAME: "; 
 				cout << it.name << endl; 	
 				cout << "ITEM ID: "; 
 				cout << it.item_ID << endl; 
 				cout << "CATEGORY: "; 
 				cout << it.category << endl; 
 				cout << "ITEM COUNT: "; 
 				cout << it.item_count << endl << endl ;
                flag = 1;
                break;
				}
				inventory.read(reinterpret_cast<char *>(&it),sizeof(it)); 
            }
                if (flag==1)
                {
                cout<<"entering new record of the item....."  << endl ;     
                cout << "Enter name of the item "<<endl;
                cin >> it.name;
                cout << "Enter the ID of the item "<<endl;
                cin >> it.item_ID;
                cout << "Enter the category of the item "<<endl;
                cin >> it.category;
                cout << "Enter the count of the item "<<endl;
                cin >> it.item_count;
                int x = inventory.tellp();
                inventory.seekp(x-sizeof(it), ios::beg);
                inventory.write(reinterpret_cast<char *>(&it),sizeof(it)); 
                }
                else 
                    cout << "No data!!";
            
    
	inventory.close(); 
            
            
    
           
           
 }
 
 
 void DeleteInventoryItem(inventory_item it)
{		
  
        fstream inventory("Inventory.txt", ios::in | ios::binary );
		fstream temp("temp.txt", ios::in | ios::binary |ios::out |ios::app);        
        inventory.read(reinterpret_cast<char *>(&it),sizeof(it)); 
        int id;
        bool flag=0;
        cout << "Enter ID of the item you wanna delete!!! " << endl;
        cin >> id ;
		
		while (!inventory.eof()) 
			{ 
 				if(id==it.item_ID)
 				{
 				cout << "The Item is deleted" << endl;
				flag=1;
				}
				inventory.read(reinterpret_cast<char *>(&it),sizeof(it)); 
            }
            
            
            if(flag==1)
            {
            	if(id!=it.item_ID)
					{
						temp.write(reinterpret_cast<char *>(&it),sizeof(it));
					}
			}
            
        
        
        
        inventory.close(); 
        temp.close();
        
        remove("Inventory.txt");
        rename("temp.txt","Inventory.txt");
 }

 void AssignInventoryItem(inventory_item it)
 {      int count=0;
        fstream inventory("Inventory.txt", ios::in |ios::out| ios::binary);
        inventory.read(reinterpret_cast<char *>(&it),sizeof(it)); 
        int itemID;
        char name[20] ;
        it.allocated_to[20][20]={};
        cout<<"What Item do you want,Enter its ID ? "<<endl;
        cin>>itemID;
        cout<<"Enter your name "<<endl;
        cin>>name;
        while (!inventory.eof()) 
			{ 
 				if(itemID==it.item_ID)
 				{
 				it.item_count--;
                strcpy(it.allocated_to[count],name);
                long situation = sizeof (it);
                inventory.seekg(-situation , ios::cur );
                inventory.write(reinterpret_cast<char *>(&it),sizeof(it));
				}
				inventory.read(reinterpret_cast<char *>(&it),sizeof(it)); 
            }
            
            count++;
        
 }
 
 
 
int main()
{   
	inventory_item it;
	p:
    int choice;
    char x;
	cout<<"-----Choose what you want to do ////!"<<endl;		
	cout<<"1.Add inventory item/s "<<endl;
	cout<<"2.View all inventory item/s "<<endl;
	cout<<"3.Search inventory item/s "<<endl;
	cout<<"4.Edit inventory item "<<endl;
	cout<<"5.Delete inventory item "<<endl;	
	cout<<"6.Assign inventory item "<<endl;	
	cout<<"7.Retrieve inventory item "<<endl;	
	cout<<"8.View the list of faculty members who have borrowed a specific item. "<<endl;
	cout<<"9.Exit"<<endl;
	cout<<"Enter what you want to do  "<<endl;
	cin>>choice;
	
	switch(choice)
	{
	case 1 :{
	do
    {
	AddInventoryItem(it);
    cout<<"Do you want to enter another item ? Enter y for it "<<endl;
    cin>>x;
	
    }while(x=='y');
    break;
    }
	case 2:{
		ViewAllInventoryItem(it);
		break;
	}
	
	case 3 :{
		SearchInventoryItem (it);
		break;
	}

	case 4 :{
		EditInventoryItem(it);
		break;
	}

	case 5 :{
		DeleteInventoryItem(it);
		break;
	}

	case 6 :{
        AssignInventoryItem(it);
		break;
	}

	case 7 :{
		break;
	}
	
	case 8 :{
		break;
	}
	
	case 9 :{
		exit(0);
		break;
	}
	
	default:{
		cout << "Invalid option please try again ! " << endl ;
		break;
	}
		
}
goto p;
	
}
