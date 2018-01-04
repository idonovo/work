#define Size 5




	
void HanoiTower(unsigned int _disc, unsigned int _from, unsigned int _to)
{
    unsigned int using = 6 - _from - _to;
    if(_disc == 1)
    {
        printf("Take disc num 1 from %d to %d\n", _from, _to);
        return;
    }
    HanoiTower(_disc - 1, _from, using);
    printf("Take disc num %d from %d to %d\n", _disc, _from, _to);
    HanoiTower(_disc - 1, using, _to);   
}
		
		
		
		
		
		
		
