int main ()

{
    std :: string str = "testeeeuuuuuuuuuuuuuuuuuuuuuuuh>12345>starscream>bumblebee";

    std :: size_t pos = str.find (">" ) ; ///zoek hoekje

    std :: string strPos = str.substr( pos +1); ///knip alles voor het 1ste >

    std :: string strPosBefore = str.substr( 0, pos); /// knipt alles na het 1ste >

    std :: size_t pos2 = strPos.find (">" );

    std :: string strPos2 = strPos.substr(pos2 +1 );

    std :: string strPos2Before = strPos.substr(0, pos2);

    std :: size_t pos3 = strPos2.find (">" );

    std :: string strPos3 = strPos2.substr(pos3 +1 );

    std :: string strPos3Before = strPos2.substr(0, pos3);

    std :: cout << '\n' << strPos << '\n' << strPos2 << '\n' << strPosBefore << '\n' << strPos2Before << '\n' << strPos3Before << '\n' << strPos3 << '\n';


    ///Print eerst de before

    return 0 ;

}
