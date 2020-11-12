
List::List()
{
	base_.data = NULL;
	base_.next = &base_;
}
void List::add(T value)
		{
			if(base_.data == NULL)
			{
				base_.data = value;
				last_ = base_;
				return;
			}
			ListItem *new_element = new ListItem;
			new_element.data = value;
			new_element.next = last_.next;
			last_.next = &new_element;
			last_ = new_element;
		}

/*void List::void del()
{
	
}

class ListException
{
	private:
		int code_;
		string message_;
	public:
		ListException(int code, string message);
		string message() const;
		int code() const;
};
*/