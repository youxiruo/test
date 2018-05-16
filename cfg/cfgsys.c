#include "../sys/sysdata.h"
#include "cfgsys.h"

#ifndef NULL
#define NULL 0
#endif


int  LowCase(char * c)
{
	if ( ( *c >= 'A' ) && ( *c <= 'Z') )
	{
	  *c = *c - 'A' +'a' ;
	 }
	return 0;
}

int DelSpaces(char *str)
{
	int i,j;
	int ret=0;
	for(i=0;str[i]!=0;i++)
	{
		if(str[i]==' '||str[i]=='\t'||str[i]=='\n')
		{
			ret++;
			for(j=i;str[j]!=0;j++)
				str[j]=str[j+1];
			i--;
		}
	}
	return ret;
}

int GetAWord(char *string,WORD_t *word)
{
	char c=0,d=0,*s;
	int  i=0,j=0,p=0,k;

	s=string;
	//c=*s;
	for(i=0;(c=s[i])!=0;i++)    
		if (IsSpace(c)==0) break;// ????
	if (c==0)
		return MMLKEY_NULL;
	p=i;
	s=&string[p];
	c=*s;

	if (c=='\'' || c=='\"')			// ????????????''""
    {
		for (j=0;(d=s[j+1])!=0;j++)
			if (d==c)		break;
		p++;	
		k=MMLKEY_STRING;			// k ???   j ????
    }
	else if(c=='[')
	{
		for (j=0;(d=s[j+1])!=0;j++)
			if (d==']')	break;
		p++;	
		k=MMLKEY_SECTION;			// k ???   j ????
	}
    else if (IsDecDigit(c))				// ??????
    {
		d=s[1];
		if (c=='0')
		{
			if(d=='x' || d=='X')
			{
				k=MMLKEY_XNUMBER;
				i+=2;
			}
			else if(d=='o' || d=='O')
			{
				k=MMLKEY_ONUMBER;
				i+=2;
			}
			else if(d=='b' || d=='B')
			{
				k=MMLKEY_BNUMBER;
				i+=2;
			}
			else k=MMLKEY_HNUMBER;
		}
		else k=MMLKEY_HNUMBER;		 
		for (j=i;(d=s[j])!=0;j++)
			if (IsHexDigit(d)==0) break;
					// k ???   j ????
    }
    else  if (IsAlpha(c))				// ??????
    {
		for (j=1;(d=s[j])!=0;j++)
		if (IsHexDigit(d)==0 && IsAlpha(d)==0) break;
		k=MMLKEY_ID;				// k ???   j ????
    }
    else  if (c=='=')
    {
		j=1;
		k=MMLKEY_EQUAL;
    }
    else if(c=='&')
	{
		d=s[1];
		if (d=='&')
		{
			j=2;
			k=MMLKEY_AND;
		}
		else
		{
			j=1;
			k=MMLKEY_TO;
		}
	}
	else if(c=='.')
	{
		j=1;
		k=MMLKEY_UNION;
	}
	else if(c==':')
	{
		for (j=1;(d=s[j])!=0;j++)
		{
			if (IsTermChar(d))
			{
				j++;
				break;
			}
		}
		k=MMLKEY_CMD;
	}
	else
    {
		//for (j=1;(d=s[j])!=0;j++)
		//if (IsHexDigit(d) || IsAlpha(d) || IsSpace(d) || d=='\'' || d=='\"' || d==';') break;
		//k=MMLKEY_CONNECTION;
		k=MMLKEY_NULL;
    }
	word->Code=k;				// ???
    word->Body=(unsigned char *)&string[p];				// ????
    word->Len=j;					// ????
	return k;
}



int Divsen(char *s,WORD_t *word)
{
	int i,j=0;
	char c;
	char d;//add at 2005-06-29
	char *p,*q;
	

	DelSpaces(s);
	for(i=0;(c=s[i])!=0;i++)
		if (IsSpace(c)==0) break;// ???
	p=&s[i];
	if (( q=strchr(p , '/' )) != NULL )
	{
		if (q[1]=='/')  *q='\0';
	}
	c=*p;
	
	for(i=0;(c=p[i])!=0;i++)
	{
		if (c=='\'' || c=='\"')			// add at 2005-06-29
		{
			for (;(d=p[i+1])!=0;i++)
				if (d==c)		
				{
					i++;
					break;
				}
		}
		LowCase(&p[i]);
	}
	for(i=0;i<4096;i++)
	{
		if (GetAWord(p,&word[i])==MMLKEY_NULL) break;
		if((word[i].Code==MMLKEY_STRING)||(word[i].Code==MMLKEY_SECTION)) j=1;
		  else j=0;
		p=(char *)&word[i].Body[word[i].Len+j];
	}
	return i;	
}

int IsLegSen(WORD_t *word,int wordcount)
{
	int i,sentence=SENTENC_NULL;

	for (i=0;i<wordcount;i++)
	{
		switch(sentence)
		{
		case SENTENC_NULL:
			if (word[i].Code!=MMLKEY_ID) return -1;	
			sentence=SENTENC_ID;
			break;
		case SENTENC_ID:
			if (word[i].Code!=MMLKEY_EQUAL) return -1;
			sentence=SENTENC_EQUAL;
			break;
		case SENTENC_EQUAL:			
			if ((word[i].Code!=MMLKEY_STRING) &&  (word[i].Code!=MMLKEY_BNUMBER)&&
				(word[i].Code!=MMLKEY_ONUMBER)&&  (word[i].Code!=MMLKEY_XNUMBER)&&
				(word[i].Code!=MMLKEY_HNUMBER) && (word[i].Code!=MMLKEY_ID))
				return -1;
			sentence=SENTENC_VALUE;
			break;
		case SENTENC_VALUE:
			if ((word[i].Code!=MMLKEY_TO) &&(word[i].Code!=MMLKEY_AND))return -1;
			if(word[i].Code==MMLKEY_NULL) return 0;
			sentence=SENTENC_CONNECTION;
			break;
		case SENTENC_CONNECTION:
			if ((word[i].Code!=MMLKEY_STRING) &&  (word[i].Code!=MMLKEY_BNUMBER)&&
				(word[i].Code!=MMLKEY_ONUMBER)&&  (word[i].Code!=MMLKEY_XNUMBER)&&
				(word[i].Code!=MMLKEY_HNUMBER) && (word[i].Code!=MMLKEY_ID))
				return -1;
			sentence=SENTENC_VALUE;
			break;
		default:
			return -1;
		}
	}
	return 0;
}


int config_com(WORD_t *word,int wordcount,int section)
{
	
	char			stringword[100];
	unsigned char	c=0;
	int	ftpindx=0;

	switch(word[0].Code)
	{
	case MMLKEY_SECTION:
		if (wordcount>1) break;
		memset(stringword,0,sizeof(stringword));
		memcpy(stringword,word[0].Body,word[0].Len);
		if(strcmp(stringword,"tcp")==0)
			section=CONFIG5_TCP;
		else if(strcmp(stringword,"udp")==0)
			section=CONFIG5_UDP;
		else if(strcmp(stringword,"sctp")==0)
			section=CONFIG5_SCTP;
		break;
	
	case MMLKEY_ID:
		if (wordcount<3) 	return section;
		if (IsLegSen(word, wordcount)==-1)	return section;
		switch(section)
		{
		case CONFIG5_TCP:
			//CmTcpSenten(word,wordcount);
			break;
		case CONFIG5_UDP:
			//CmUdpSenten(word,wordcount);
			break;
		default:
			break;
		}
	default:
		break;
	}
	
	return section;
}


int configcomm(unsigned char *filename)
{
    FILE *fp;
	char sItem[8192];
	WORD_t word[MAXWORDNUMALINE];
	int    wordcount;
	int    section;
	int    count;
	
	//打开文件
	if((fp=Fopen(filename,"r"))==NULL)
	{
		return -1;
	}

	while(Fgets(sItem,8192,fp) != NULL)
	{
		memset(word,0,10*sizeof(WORD_t));//为什么10个？
		wordcount=Divsen(sItem,word);
		if(wordcount<=0)continue;
		section=config_com(word,wordcount,section);
		memset(sItem,0,sizeof(sItem));
		count++;
	}

}

