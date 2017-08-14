#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define STRMAX 100
struct Song{
	char title[STRMAX];
	char artist[STRMAX];
	int year_published;
};

#define SONGMAX 1024
struct Song music_library[SONGMAX];
int current_number_of_songs = 0;

char library_name[STRMAX];


FILE * open_file(const char * file_name, char * c)
{
    FILE *ifp;
    ifp = fopen(file_name, c);
    if( ifp == NULL)
    {
        fprintf(stderr, "Creating new file named %s\n", file_name);
    }
    return ifp;
	
}

void str_to_lower(char * str)
{
    int len= strlen(str);
    for(int i = 0; i < len; i++)
    {
        str[i] = tolower(str[i]);
    }
}

// binary search
int find_index_of_song_with_name(char * title)
{
    int L = 0, R = current_number_of_songs - 1, M =(L + R) / 2;
    char temp[STRMAX];
    str_to_lower(title);
    for(;L <= R; M = (L + R) / 2 )
    {
       strcpy(temp, music_library[M].title);
       str_to_lower(temp);
       if(strcmp(temp, title) < 0)
       {
           L = M + 1;
           
       }
       else if(strcmp(temp, title) > 0)
       {
          
          R = M - 1;
       } 
       else if(strcmp(temp, title) == 0)
       {
           return M;
       }
    }
    return -1;

}
void prompt_for_song(char * item)
{
    int i;
    printf("Title: ");
    fgets(item, STRMAX, stdin);
    i = strlen(item) - 1;
    item[i] = '\0';
}
// binary search for L
void find_song()
{
    char searchItem[STRMAX];
    int i;
    prompt_for_song(searchItem);
    i = find_index_of_song_with_name(searchItem);
    if(i != -1)
    {
        printf("%d Title: %s, Artist: %s, Year Published: %d\n", i, music_library[i].title, music_library[i].artist, music_library[i].year_published);
    }
    
}

// end of search array
int find_index_for_new_song(struct Song newsong)
{
    char copyNewSong[STRMAX], songfromlist[STRMAX];
    strcpy(copyNewSong, newsong.title);
    str_to_lower(copyNewSong); 
    for(int i = 0; i < current_number_of_songs; i++)
    {
        strcpy(songfromlist, music_library[i].title);
        str_to_lower(songfromlist);
        if(strcmp(copyNewSong,songfromlist) < 0)
        {
 		return i;
        }
    } 
    return current_number_of_songs;
}


void crunch_up_from_index(int i)
{
    struct Song temp;
    for(int index = current_number_of_songs - 1 ;i < index;index--)
    {
        strcpy(music_library[index].title, music_library[index - 1].title);
        strcpy(music_library[index].artist, music_library[index - 1].artist);
        music_library[index].year_published = music_library[index - 1].year_published;
    }

}

void copy_song_to_library(struct Song * structptr, int i)
{
    strcpy(music_library[i].title, (*structptr).title);
    strcpy(music_library[i].artist, (*structptr).artist);
    music_library[i].year_published = (*structptr).year_published;
}
void add_song_to_MusicLibrary(struct Song newsong)
{
    int i;
    i =find_index_for_new_song(newsong);
    current_number_of_songs++;
    crunch_up_from_index(i);
    copy_song_to_library(&newsong, i);
    
}

void flush_buffer()
{
    char c;
    c = getchar();
}

int get_input_year()
{
    int newYear;
    printf("Year Published: ");
    scanf("%d", &newYear);
    flush_buffer();
    return newYear;
}
void get_input_artist(char * artist)
{
    int i;
    printf("Artist: ");
    fgets(artist, STRMAX, stdin);
    i = strlen(artist) - 1;
    artist[i] = '\0';   
}
void  get_input_title(char * title)
{
    int i;
    printf("Title: ");
    fgets(title, STRMAX, stdin);    
    i = strlen(title) - 1;
    title[i] = '\0';
    
}
void prompt_for_new_song_info()
{
    struct Song newsong;
    get_input_title(newsong.title);
    get_input_artist(newsong.artist);
    newsong.year_published = get_input_year();
    add_song_to_MusicLibrary(newsong);
}

// block for deleting a song
void crunch_down_from_index(int index)
{
    for(int i = index; i < current_number_of_songs; i++)
    {
       strcpy(music_library[i].title, music_library[i + 1].title);
       strcpy(music_library[i].artist, music_library[i + 1].artist);
       music_library[i].year_published = music_library[i + 1].year_published;
    }

}
void remove_song_from_MusicLibrary_by_name()
{
    char searchTitle[STRMAX];
    int index;
    get_input_title(searchTitle);
    index = find_index_of_song_with_name(searchTitle);
    if(index >= 0)
    {
        crunch_down_from_index(index);
        current_number_of_songs--;
    }
}
//end of removing song
void print_MusicLibrary(int choice)
{
    if(choice)
    {
        for(int i = 0; i < current_number_of_songs; i++)
        {
		printf("%d Title: %s, Artist: %s, Year Published: %d\n", i, music_library[i].title, music_library[i].artist, music_library[i].year_published);
        }
    }
}

FILE * write_song(FILE * ofp)
{
    for(int i = 0; i < current_number_of_songs; i++)
    {
        fprintf(ofp, "$%s$ $%s$ %d\n", music_library[i].title, music_library[i].artist, music_library[i].year_published);
    }
    return ofp;
}
void add_dat_extension()
{
   strcat(library_name, ".dat");
   
}
void store_MusicLibrary()
{
    add_dat_extension();
    FILE * ofp = open_file(library_name, "w");
    if(ofp != NULL)
    {
        ofp = write_song(ofp);
	fclose(ofp);
    }   
}
void evaluate_command(char c)
{
    switch(c)
    {
        case 'i':
 	case 'I':
	    prompt_for_new_song_info();
            break;
        case 'p':
	case 'P':
  	    print_MusicLibrary(TRUE);
	    break;
	case 'D':
	case 'd':
	    remove_song_from_MusicLibrary_by_name();
	    break;
	case 'L':
	case 'l':
	    find_song();
	    break;
        case 'Q':
        case 'q':
            store_MusicLibrary();
	    break;
        default:
            printf("Invalid input\n");
	    break;

    }
}
char read_command()
{
    char newc = '\n', garbage;
    while(TRUE)
    {
        printf("\n%s Command: \n", library_name);
        newc = getchar();
        if(newc == ' ' || newc == '\t' || newc == '\n')
        {
            continue;
        }
	while(garbage = getchar() != '\n' && garbage != EOF){}
            return newc;        

    }
       
}
void get_library_name(char * file_name)
{
    int i;
    for(i = 0;  file_name[i] != '.' && file_name[i] != '\0'; i++)
    {
	library_name[i] = file_name[i];
    }
    library_name[i] = '\0';
}

void handle_commands(char * file_name)
{
    char  c = '\0';
    get_library_name(file_name);
    while(c != 'Q' && c !=  'q')
    {
        c = read_command();
        evaluate_command(c);
    }
}

void load_new_song_to_MusicLibrary(struct Song NewSong)
{
    music_library[current_number_of_songs] = NewSong;
    current_number_of_songs++;
}

void read_song(char * NewTitle, char * NewArtist, char * NewYear)
{
    struct Song NewSong;
    strcpy(NewSong.title,NewTitle);
    strcpy(NewSong.artist, NewArtist);
    NewSong.year_published = atoi(NewYear);
    load_new_song_to_MusicLibrary(NewSong);

}

FILE * load_MusicLibrary(FILE * ifp)
{
    char  newTitle[STRMAX], newArtist[STRMAX], newYear[5];
    char  templine[300]; 
    while(fgets(templine, 300, ifp) != NULL)    {
        sscanf(templine, " $%[^$]$ $%[^$]$ %s", &newTitle, &newArtist, & newYear);
	
        read_song(newTitle, newArtist, newYear);
    } 
    return ifp;
}

void manage_music_library(char * file_name)
{
    FILE * ifp = open_file(file_name, "r");
    if(ifp != NULL)
    {
        ifp = load_MusicLibrary(ifp);
	fclose(ifp);
    }
    handle_commands(file_name);
}

int main(int argc, char* argv[])
{
    char *  default_name = "myMusic.dat";
    char  * file_name = argc == 1 ? default_name: argv[1];
    manage_music_library(file_name);
    return 0;
}
