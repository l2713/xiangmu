//二叉搜索树管理图书分类，每个分类结点包含一个单向链表存储图书信息
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义图书信息结构体.表示一本书基本信息
typedef struct Book 
{
    char title[100];//书名
    char author[100];//作者
    int year;//出版年龄
    struct Book* next;//同类型指向下一本书的指针，用于构造链表
} Book;
getchar();//缓冲
// 定义分类节点结构体，表示一个图书分类结点
typedef struct CategoryNode 
{
    char categoryName[100];//字符数组，存储分类名称
    Book* bookList;//指向该分类下图书链表的指针
    struct CategoryNode* left;//左节点
    struct CategoryNode* right;//右节点，用于构造二叉树搜索树
} CategoryNode;

// 创建新图书，构建一个新的book结构体
Book* createBook(char* title,char* author,int year) //传入图书信息参数
{
    Book* newBook = (Book*)malloc(sizeof(Book));//动态分配内存，book类型
    strncpy(newBook->title, title, sizeof(newBook->title) - 1);//复制书名
    newBook->title[sizeof(newBook->title) - 1] = '\0';//确保字符串以'\0'结尾
    strncpy(newBook->author, author, sizeof(newBook->author) - 1);//复制作者
    newBook->author[sizeof(newBook->author) - 1] = '\0';//确保字符串以'\0'结尾
    newBook->year = year;//设置出版年份
    newBook->next = NULL;//初始化next指向空，为链表中的最后一个结点
    return newBook;
}

// 添加图书到链表（尾插法）
void addBook(Book** head, Book* newBook) 
{
    if (*head == NULL)
    {//如果链表为空
        *head = newBook;//新书作为头结点
    }
    else 
    {
        Book* temp = *head;//创建一个指针，指向链表头
        while (temp->next != NULL) 
        {//遍历链表，找最后一个结点
            temp = temp->next;
        }
        temp->next = newBook;//新书添加到末尾
    }
}

// 显示图书信息（打印链表中的所有图书信息）
void displayBooks(Book* head) 
{
    Book* temp = head;
    while (temp != NULL) 
    {//链表不为空，不断地打印
        printf("Title: %s, Author: %s, Year: %d\n", temp->title, temp->author, temp->year);
        temp = temp->next;//移到下一个结点，直到末尾
    }
}

// 查找图书
Book* findBook(Book* head, const char* title) 
{
    Book* temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->title, title) == 0)
        {//如果要查找的书找到了对应的
            return temp;//返回当前指针
        }
        temp = temp->next;//不然就一直找下一个
    }
    return NULL;
}

// 删除图书
void deleteBook(Book** head, const char* title) 
{
    //构造两个指针
    Book* temp = *head;//当前结点（初始化指向头结点）
    Book* prev = NULL;//前一个结点

    if (temp != NULL && strcmp(temp->title, title) == 0) 
    {//如果头结点就是要删除的结点
        *head = temp->next;//调整头指针
        free(temp);//释放内存
        return;
    }

    while (temp != NULL && strcmp(temp->title, title) != 0) 
    {//temp为要删除的结点
        prev = temp;//将temp作为上一个结点
        temp = temp->next;//遍历链表
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;//调整指针
    free(temp);//释放内存
}

// 创建分类节点
CategoryNode* createCategoryNode(char* categoryName) //传入分类名称参数
{
    CategoryNode* newNode = (CategoryNode*)malloc(sizeof(CategoryNode));//动态分配内存
    strncpy(newNode->categoryName, categoryName, sizeof(newNode->categoryName) - 1);//复制传入的分类名称
    newNode->categoryName[sizeof(newNode->categoryName) - 1] = '\0';//字符串末尾添加'\0'
    //初始化
    newNode->bookList = NULL;//分类下还没有图书
    newNode->left = NULL;//没有左子节点
    newNode->right = NULL;//没有右子节点
    return newNode;
}

// 插入分类节点到树中
CategoryNode* insertCategoryNode(CategoryNode* root,char* categoryName) 
{
    if (root == NULL) //树为空
    {//调用创建分类节点函数并返回
        return createCategoryNode(categoryName);
    }

    if (strcmp(categoryName, root->categoryName) < 0) 
    {//如果传入的分类名称小于当前结点的分类名称（左子树并没有遍历完全）
        root->left = insertCategoryNode(root->left, categoryName);//递归插入到左子树
    }
    else if (strcmp(categoryName, root->categoryName) > 0) 
    {//如果传入的分类名称大于当前节点的分类名称（左子树已经被遍历完全，要接着遍历右子树）
        root->right = insertCategoryNode(root->right, categoryName);//递归插入到右子树
    }

    return root;
}

// 查找分类节点
CategoryNode* findCategoryNode(CategoryNode* root, const char* categoryName)
{
    if (root == NULL || strcmp(root->categoryName, categoryName) == 0)
    {//如果当前结点为空或者找到了目标节点
        return root;//返回这个结点
    }

    if (strcmp(categoryName, root->categoryName) < 0) 
    {//如果目标分类小于当前结点分类名称（左子树没有被遍历完全）
        return findCategoryNode(root->left, categoryName);//递归在左子树中查找
    }

    return findCategoryNode(root->right, categoryName);//否则在右子树中查找
}

// 显示分类及其图书
void displayCategory(CategoryNode* root) 
{
    if (root != NULL)
    {
        displayCategory(root->left);//以左节点为结点，递归遍历
        printf("Category: %s\n", root->categoryName);//打印当前分类名称
        displayBooks(root->bookList);//调用显示信息函数
        displayCategory(root->right);//再以右节点为结点，递归遍历
    }
}

int main() 
{
    CategoryNode* root = NULL;//初始化分类树结点为空
    int choice;//做出的选择
    char categoryName[100];
    char title[100];
    char author[100];
    int year;

    while (1) {
        printf("\n1. Add Category\n2. Add Book\n3. Display All\n4. Find Book\n5. Delete Book\n6. Exit\n");
        printf("Enter your choice: ");//提醒输入
        scanf("%d", &choice);//做出选择
        getchar(); // 清除输入缓冲区

        switch (choice)
        {
        case 1:
            //添加分类
            printf("Enter category name: ");//输入分类名称
            fgets(categoryName, sizeof(categoryName), stdin);//读取分类名称
            categoryName[strcspn(categoryName, "\n")] = '\0'; // 去掉换行符
            root = insertCategoryNode(root, categoryName);//调用插入分类结点函数插入结点
            break;
        case 2:
            //添加图书
            printf("Enter category name: ");//输入分类名称
            fgets(categoryName, sizeof(categoryName), stdin);//读取分类名称
            categoryName[strcspn(categoryName, "\n")] = '\0';//去掉换行符
            CategoryNode* category = findCategoryNode(root, categoryName);//查找分类结点
            if (category == NULL) //如果分类结点不存在，提示错误
            {
                printf("Category not found!\n");
            }
            else {
                printf("Enter book title: ");//用户输入书名
                fgets(title, sizeof(title), stdin);//读取书名
                title[strcspn(title, "\n")] = '\0';//去掉换行符
                printf("Enter book author: ");//输入作者
                fgets(author, sizeof(author), stdin);//读取作者
                author[strcspn(author, "\n")] = '\0';//去掉换行符
                printf("Enter book year: ");
                scanf("%d", &year);//输入出版年份
                getchar(); // 清除输入缓冲区
                Book* newBook = createBook(title, author, year);//创建新书
                addBook(&category->bookList, newBook);//新书添加到分类的图书链表中
            }
            break;
        case 3:
            //显示所有分类及其图书
            displayCategory(root);//调用displayCategory函数，显示所有图书信息
            break;
        case 4:
            //查找图书
            printf("Enter book title to find: ");//输入书名
            fgets(title, sizeof(title), stdin);//读取书名
            title[strcspn(title, "\n")] = '\0';//去掉换行符
            CategoryNode* temp = root;//创建一个临时指针，指向根结点
            Book* foundBook = NULL;//初始化founfbook为NULL
            while (temp != NULL)//遍历分类树
            {
                foundBook = findBook(temp->bookList, title);//在当前分类的图书链表中查找图书
                if (foundBook != NULL)//如果找到匹配的图书
                {
                    printf("Book found in category: %s\n", temp->categoryName);//打印分类名称
                    printf("Title: %s, Author: %s, Year: %d\n", foundBook->title, foundBook->author, foundBook->year);//打印图书信息
                    break;
                }
                temp = temp->right;//指向下一个分类结点，继续寻找
            }
            if (foundBook == NULL)//如果为找到匹配的图书，提示错误
            {
                printf("Book not found!\n");
            }
            break;
        case 5:
            //删除图书
            printf("Enter category name: ");//输入分类名称
            fgets(categoryName, sizeof(categoryName), stdin);//读取分类名称
            categoryName[strcspn(categoryName, "\n")] = '\0';//去掉换行符
            category = findCategoryNode(root, categoryName);//查找分类结点
            if (category == NULL) //如果分类结点不存在
            {
                printf("Category not found!\n");//显示错误
            }
            else {
                printf("Enter book title to delete: ");//输入删除的书名
                fgets(title, sizeof(title), stdin);//读取书名
                title[strcspn(title, "\n")] = '\0';//去掉换行符
                deleteBook(&category->bookList, title);//调用deleteBook函数删除图书
            }
            break;
        case 6:
            exit(0);//退出程序
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}