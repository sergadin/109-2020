typedef struct StuLst
{
  struct StuLst *NextPtr;
  char   FIO[120];
  int    Group;
  int    MiddleNumber;
}StudentsList;


typedef struct TrDB
{
  struct TrDB *LeftNode;
  struct TrDB *RightNode;
  struct StuLst *FirstStudent;
  int NodeNumber;
}TreeDataBase;


class StudentsDB
{
  public:

    TreeDataBase *Root;
    StudentsList *NewStudent;
    StudentsList *DelRec;
    StudentsList *FindRec;
    int NodeCounter;
    int TreeLevel;

    int FillIn(TreeDataBase *);
    void Print(TreeDataBase *, int);
    int SaveFile(TreeDataBase *);
    int AddRecord(TreeDataBase *);
    void DeleteRecord(TreeDataBase *);
    void FindRecord(TreeDataBase *,int);
    void ChangeRecord(TreeDataBase *);
};
