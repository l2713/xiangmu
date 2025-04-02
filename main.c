//��������������ͼ����࣬ÿ�����������һ����������洢ͼ����Ϣ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����ͼ����Ϣ�ṹ��.��ʾһ���������Ϣ
typedef struct Book 
{
    char title[100];//����
    char author[100];//����
    int year;//��������
    struct Book* next;//ͬ����ָ����һ�����ָ�룬���ڹ�������
} Book;
getchar();//����
// �������ڵ�ṹ�壬��ʾһ��ͼ�������
typedef struct CategoryNode 
{
    char categoryName[100];//�ַ����飬�洢��������
    Book* bookList;//ָ��÷�����ͼ�������ָ��
    struct CategoryNode* left;//��ڵ�
    struct CategoryNode* right;//�ҽڵ㣬���ڹ��������������
} CategoryNode;

// ������ͼ�飬����һ���µ�book�ṹ��
Book* createBook(char* title,char* author,int year) //����ͼ����Ϣ����
{
    Book* newBook = (Book*)malloc(sizeof(Book));//��̬�����ڴ棬book����
    strncpy(newBook->title, title, sizeof(newBook->title) - 1);//��������
    newBook->title[sizeof(newBook->title) - 1] = '\0';//ȷ���ַ�����'\0'��β
    strncpy(newBook->author, author, sizeof(newBook->author) - 1);//��������
    newBook->author[sizeof(newBook->author) - 1] = '\0';//ȷ���ַ�����'\0'��β
    newBook->year = year;//���ó������
    newBook->next = NULL;//��ʼ��nextָ��գ�Ϊ�����е����һ�����
    return newBook;
}

// ���ͼ�鵽����β�巨��
void addBook(Book** head, Book* newBook) 
{
    if (*head == NULL)
    {//�������Ϊ��
        *head = newBook;//������Ϊͷ���
    }
    else 
    {
        Book* temp = *head;//����һ��ָ�룬ָ������ͷ
        while (temp->next != NULL) 
        {//�������������һ�����
            temp = temp->next;
        }
        temp->next = newBook;//������ӵ�ĩβ
    }
}

// ��ʾͼ����Ϣ����ӡ�����е�����ͼ����Ϣ��
void displayBooks(Book* head) 
{
    Book* temp = head;
    while (temp != NULL) 
    {//����Ϊ�գ����ϵش�ӡ
        printf("Title: %s, Author: %s, Year: %d\n", temp->title, temp->author, temp->year);
        temp = temp->next;//�Ƶ���һ����㣬ֱ��ĩβ
    }
}

// ����ͼ��
Book* findBook(Book* head, const char* title) 
{
    Book* temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->title, title) == 0)
        {//���Ҫ���ҵ����ҵ��˶�Ӧ��
            return temp;//���ص�ǰָ��
        }
        temp = temp->next;//��Ȼ��һֱ����һ��
    }
    return NULL;
}

// ɾ��ͼ��
void deleteBook(Book** head, const char* title) 
{
    //��������ָ��
    Book* temp = *head;//��ǰ��㣨��ʼ��ָ��ͷ��㣩
    Book* prev = NULL;//ǰһ�����

    if (temp != NULL && strcmp(temp->title, title) == 0) 
    {//���ͷ������Ҫɾ���Ľ��
        *head = temp->next;//����ͷָ��
        free(temp);//�ͷ��ڴ�
        return;
    }

    while (temp != NULL && strcmp(temp->title, title) != 0) 
    {//tempΪҪɾ���Ľ��
        prev = temp;//��temp��Ϊ��һ�����
        temp = temp->next;//��������
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;//����ָ��
    free(temp);//�ͷ��ڴ�
}

// ��������ڵ�
CategoryNode* createCategoryNode(char* categoryName) //����������Ʋ���
{
    CategoryNode* newNode = (CategoryNode*)malloc(sizeof(CategoryNode));//��̬�����ڴ�
    strncpy(newNode->categoryName, categoryName, sizeof(newNode->categoryName) - 1);//���ƴ���ķ�������
    newNode->categoryName[sizeof(newNode->categoryName) - 1] = '\0';//�ַ���ĩβ���'\0'
    //��ʼ��
    newNode->bookList = NULL;//�����»�û��ͼ��
    newNode->left = NULL;//û�����ӽڵ�
    newNode->right = NULL;//û�����ӽڵ�
    return newNode;
}

// �������ڵ㵽����
CategoryNode* insertCategoryNode(CategoryNode* root,char* categoryName) 
{
    if (root == NULL) //��Ϊ��
    {//���ô�������ڵ㺯��������
        return createCategoryNode(categoryName);
    }

    if (strcmp(categoryName, root->categoryName) < 0) 
    {//�������ķ�������С�ڵ�ǰ���ķ������ƣ���������û�б�����ȫ��
        root->left = insertCategoryNode(root->left, categoryName);//�ݹ���뵽������
    }
    else if (strcmp(categoryName, root->categoryName) > 0) 
    {//�������ķ������ƴ��ڵ�ǰ�ڵ�ķ������ƣ��������Ѿ���������ȫ��Ҫ���ű�����������
        root->right = insertCategoryNode(root->right, categoryName);//�ݹ���뵽������
    }

    return root;
}

// ���ҷ���ڵ�
CategoryNode* findCategoryNode(CategoryNode* root, const char* categoryName)
{
    if (root == NULL || strcmp(root->categoryName, categoryName) == 0)
    {//�����ǰ���Ϊ�ջ����ҵ���Ŀ��ڵ�
        return root;//����������
    }

    if (strcmp(categoryName, root->categoryName) < 0) 
    {//���Ŀ�����С�ڵ�ǰ���������ƣ�������û�б�������ȫ��
        return findCategoryNode(root->left, categoryName);//�ݹ����������в���
    }

    return findCategoryNode(root->right, categoryName);//�������������в���
}

// ��ʾ���༰��ͼ��
void displayCategory(CategoryNode* root) 
{
    if (root != NULL)
    {
        displayCategory(root->left);//����ڵ�Ϊ��㣬�ݹ����
        printf("Category: %s\n", root->categoryName);//��ӡ��ǰ��������
        displayBooks(root->bookList);//������ʾ��Ϣ����
        displayCategory(root->right);//�����ҽڵ�Ϊ��㣬�ݹ����
    }
}

int main() 
{
    CategoryNode* root = NULL;//��ʼ�����������Ϊ��
    int choice;//������ѡ��
    char categoryName[100];
    char title[100];
    char author[100];
    int year;

    while (1) {
        printf("\n1. Add Category\n2. Add Book\n3. Display All\n4. Find Book\n5. Delete Book\n6. Exit\n");
        printf("Enter your choice: ");//��������
        scanf("%d", &choice);//����ѡ��
        getchar(); // ������뻺����

        switch (choice)
        {
        case 1:
            //��ӷ���
            printf("Enter category name: ");//�����������
            fgets(categoryName, sizeof(categoryName), stdin);//��ȡ��������
            categoryName[strcspn(categoryName, "\n")] = '\0'; // ȥ�����з�
            root = insertCategoryNode(root, categoryName);//���ò�������㺯��������
            break;
        case 2:
            //���ͼ��
            printf("Enter category name: ");//�����������
            fgets(categoryName, sizeof(categoryName), stdin);//��ȡ��������
            categoryName[strcspn(categoryName, "\n")] = '\0';//ȥ�����з�
            CategoryNode* category = findCategoryNode(root, categoryName);//���ҷ�����
            if (category == NULL) //��������㲻���ڣ���ʾ����
            {
                printf("Category not found!\n");
            }
            else {
                printf("Enter book title: ");//�û���������
                fgets(title, sizeof(title), stdin);//��ȡ����
                title[strcspn(title, "\n")] = '\0';//ȥ�����з�
                printf("Enter book author: ");//��������
                fgets(author, sizeof(author), stdin);//��ȡ����
                author[strcspn(author, "\n")] = '\0';//ȥ�����з�
                printf("Enter book year: ");
                scanf("%d", &year);//����������
                getchar(); // ������뻺����
                Book* newBook = createBook(title, author, year);//��������
                addBook(&category->bookList, newBook);//������ӵ������ͼ��������
            }
            break;
        case 3:
            //��ʾ���з��༰��ͼ��
            displayCategory(root);//����displayCategory��������ʾ����ͼ����Ϣ
            break;
        case 4:
            //����ͼ��
            printf("Enter book title to find: ");//��������
            fgets(title, sizeof(title), stdin);//��ȡ����
            title[strcspn(title, "\n")] = '\0';//ȥ�����з�
            CategoryNode* temp = root;//����һ����ʱָ�룬ָ������
            Book* foundBook = NULL;//��ʼ��founfbookΪNULL
            while (temp != NULL)//����������
            {
                foundBook = findBook(temp->bookList, title);//�ڵ�ǰ�����ͼ�������в���ͼ��
                if (foundBook != NULL)//����ҵ�ƥ���ͼ��
                {
                    printf("Book found in category: %s\n", temp->categoryName);//��ӡ��������
                    printf("Title: %s, Author: %s, Year: %d\n", foundBook->title, foundBook->author, foundBook->year);//��ӡͼ����Ϣ
                    break;
                }
                temp = temp->right;//ָ����һ�������㣬����Ѱ��
            }
            if (foundBook == NULL)//���Ϊ�ҵ�ƥ���ͼ�飬��ʾ����
            {
                printf("Book not found!\n");
            }
            break;
        case 5:
            //ɾ��ͼ��
            printf("Enter category name: ");//�����������
            fgets(categoryName, sizeof(categoryName), stdin);//��ȡ��������
            categoryName[strcspn(categoryName, "\n")] = '\0';//ȥ�����з�
            category = findCategoryNode(root, categoryName);//���ҷ�����
            if (category == NULL) //��������㲻����
            {
                printf("Category not found!\n");//��ʾ����
            }
            else {
                printf("Enter book title to delete: ");//����ɾ��������
                fgets(title, sizeof(title), stdin);//��ȡ����
                title[strcspn(title, "\n")] = '\0';//ȥ�����з�
                deleteBook(&category->bookList, title);//����deleteBook����ɾ��ͼ��
            }
            break;
        case 6:
            exit(0);//�˳�����
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}