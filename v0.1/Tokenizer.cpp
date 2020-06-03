#include <cctype>
#include <iostream>
#include <cinttypes>
#include <cstring>
#include <bitset>
#include "Tokenizer.hpp"
#include "Debug.hpp"

#include <assert.h>

#define tP tokenPack

Tokenizer::Tokenizer(TokenPack *_tokenPack)
{
    tokenPack = _tokenPack;

    tokenTreeStack.push_back(0);

    identifierCounter = 0;

    c = '\0';
    pc = '\0';
    
    escapeNext = false;
    state = TokenizerState::Normal;

    charBuffer = std::string();
}

inline bool Tokenizer::IsValidIdentifierChar(char ch, bool first)
{
    //if (isalpha(ch) || ch == '_' || ch == '-' || ch == '/' || ch == '+' || ch == '%' || ch == '*' || (first == false && isdigit(ch)))
    if (isalpha(ch) || ch == '_' || ch == '-' || ch == '/' || ch == '+' || ch == '%' || ch == '*' || (first == false && isdigit(ch)))

        return true;

    return false;
}

inline void Tokenizer::ResetBuffer()
{
    charBuffer.clear();
}

inline void Tokenizer::ResetAll()
{
    pc = '\0';
    c = '\0';
    escapeNext = false;
    
    ResetBuffer();
}

std::string TokenPack::GetIdentifierById(std::size_t id)
{
    for (auto it = identifiers.begin(); it != identifiers.end(); ++it)
        if (it->second == id)
            return it->first;
    return nullptr;
}

void TokenPack::Debug()
{
    std::cout << "\n\nDebug:\n\n";

    //std::cout<<"pc:'"<<pc<<"' c:'"<<c<<"' charBuffer:'"<<charBuffer<<"'\n\n";

    std::cout << "\n\nStored stings:\n";

    for (int i = 0; i < stringData.size(); i++)
    {
        std::cout << "{" << stringData[i] << "}\n";
    }

    std::cout << "\n\nStored identifiers:\n";

    for (auto it = identifiers.begin(); it != identifiers.end(); ++it)
        std::cout << "{" << it->first << "}\n";

    /*
std::cout<<"\n\nTokenStack:\n";

for(int i = 0; i < tokenTreeStack.size(); i++){
std::cout<<tokenTreeStack[i]<<",";
}
*/

    std::cout << "\n\nTokens:\n";

    for (int i = 0; i < tokens.size(); i++)
    {
        std::cout << "group:" << GetTokenGroup(tokens[i].ptr) << " data:" << GetTokenData(tokens[i].ptr) << " : " << TokenTypeStrings.lower_bound((TokenType)tokens[i].ptr)->second << "\n";
    }
}

void TokenPack::DebugStep(Tokenizer *t)
{
    //return;

    std::cout << "\n\nDebugStep:\n\n";

    std::cout << "pc:'" << t->pc << "' c:'" << t->c << "' charBuffer:'" << t->charBuffer << "'\n\n";

    std::cout << "\n\nStored stings:\n";

    for (int i = 0; i < stringData.size(); i++)
    {
        std::cout << "{" << stringData[i] << "}\n";
    }

    std::cout << "\n\nStored identifiers:\n";

    for (auto it = identifiers.begin(); it != identifiers.end(); ++it)
        std::cout << "{" << it->first << "}\n";

    std::cout << "\n\nTokenStack:\n";

    for (int i = 0; i < t->tokenTreeStack.size(); i++)
    {
        std::cout << t->tokenTreeStack[i] << ",";
    }

    std::cout << "\n\nTokens:\n";

    for (int i = 0; i < tokens.size(); i++)
    {
        std::cout << "group:" << GetTokenGroup(tokens[i].ptr) << " data:" << GetTokenData(tokens[i].ptr) << " : " << TokenTypeStrings.lower_bound((TokenType)tokens[i].ptr)->second << "\n";
    }
}

inline void TokenPack::AddToken(Tokenizer *t, TokenType tokenType)
{
    AddToken(t, {static_cast<std::size_t>(tokenType)});
}

inline void TokenPack::AddToken(Tokenizer *t, Token token)
{
    tokens.push_back(token);
    for (int i = 0; i < t->tokenTreeStack.size(); i++)
        t->tokenTreeStack[i]++;

    ///////////////////////////////////////////////////////
    DebugStep(t);
}

inline Token TokenPack::StoreString(Tokenizer *t)
{
    std::size_t index = stringData.size();
    stringData.push_back(t->charBuffer);
    return {index};
}

inline Token TokenPack::StoreIdentifier(Tokenizer *t)
{
    auto idFind = identifiers.find(t->charBuffer);
    std::size_t idc = 0;
    if (idFind == identifiers.end())
    {
        idc = t->identifierCounter++;
        identifiers[t->charBuffer] = idc;
    }
    else
    {
        idc = idFind->second;
    }
    return {idc};
}

void TokenPack::AddLiteralIdentifier(Tokenizer *t)
{
    AddToken(t, TokenType::LiteralIdentifier);
    AddToken(t, StoreString(t));

    t->ResetBuffer();
}

void TokenPack::AddLiteralString(Tokenizer *t)
{
    AddToken(t, TokenType::LiteralString);
    AddToken(t, StoreString(t));

    t->ResetBuffer();
}

void TokenPack::AddLiteralInteger(Tokenizer *t)
{
    AddToken(t, TokenType::LiteralInteger);

    //std::size_t numConverted;
    std::intmax_t num = std::strtoimax(t->charBuffer.c_str(), nullptr, 10);
    AddToken(t, Token{.i=num});

    //std::memcpy(&numConverted, &num, sizeof(std::size_t));

    //AddToken(t, numConverted);

    t->ResetBuffer();
}

void TokenPack::AddLiteralDecimal(Tokenizer *t)
{
    AddToken(t, TokenType::LiteralDecimal);

    //std::size_t numConverted;
    double num = std::strtod(t->charBuffer.c_str(), nullptr);
    AddToken(t, Token{.d=num});
    //std::memcpy(&numConverted, &num, sizeof(std::size_t));

    t->ResetBuffer();
}


bool TokenPack::AddIdentifier(Tokenizer *t)
{
    if (t->charBuffer.size() == 0)
        return false;

    if (t->state == TokenizerState::InInteger)
        AddLiteralInteger(t);
    else if (t->state == TokenizerState::InDecimal)
        AddLiteralDecimal(t);
    else if (t->state == TokenizerState::InIdentifier)
        AddLiteralIdentifier(t);
    else
    {
        if (t->charBuffer.compare("ret"))
            AddToken(t, TokenType::Return);
        else if (t->charBuffer.compare("null"))
            AddToken(t, TokenType::Null);
        else
        {
            AddToken(t, TokenType::Identifier);

            AddToken(t, {t->identifierCounter});
            identifiers[t->charBuffer] = t->identifierCounter++;
        }
        
        t->ResetBuffer();
    }
    
    t->state = TokenizerState::Normal;

    return true;
}

//check if pc and c match the 2 letter string pattern
#define S2(STR) (pc == STR[0] && c == STR[1])

//(c==STR[IND]) if IND is in range, else true 
#define cIt(STR,IND) ((IND<sizeof(STR))?(c==STR[IND]):true)
//(pc==STR[IND]) if IND is in range, else true
//#define pIt(STR,IND) ((IND<sizeof(STR))?(pc==STR[IND]):true)
//(c==STR[IND]) if IND is in range, else false
#define cIf(STR,IND) ((IND<sizeof(STR))?(c==STR[IND]):false)
//(pc==STR[IND]) if IND is in range, else false
//#define pIf(STR,IND) ((IND<sizeof(STR))?(pc==STR[IND]):false)

//is c any of these chars in the STR
#define C(STR) (cIf(STR,0)||cIf(STR,1)||cIf(STR,2)||cIf(STR,3)||cIf(STR,4)||cIf(STR,5)||cIf(STR,6)||cIf(STR,7)||cIf(STR,8)||cIf(STR,9)||cIf(STR,10)||cIf(STR,11))
//is pc any of these chars in the STR
//#define P(STR) (pIf(STR,0)||pIf(STR,1)||pIf(STR,2)||pIf(STR,3)||pIf(STR,4)||pIf(STR,5)||pIf(STR,6)||pIf(STR,7)||pIf(STR,8)||pIf(STR,9)||pIf(STR,10)||pIf(STR,11))

bool Tokenizer::HandleComments(unsigned int helperStateGroup){
	
	//See if you should exit comment mode
	if (helperStateGroup == TokenizerState_InComment)
    {
        //Exit comment mode or stay, either way handled = true
        
        if (state == TokenizerState::InComment && C("\n\r"))
            state = TokenizerState::Normal;
        else if (S2("*/")) //&&(state == TokenizerState::InCommentMultiline)
            state = TokenizerState::Normal;
        
        return true;
    }
    //See if you should enter comment mode
    else if(pc == '/' && helperStateGroup == TokenizerState_Normal)
    {
        if(c=='*'){
            state == TokenizerState::InCommentMultiline;
            return true;
        }
        else if(c=='/'){
            state == TokenizerState::InComment;
            return true;
        }
    }

    return false;
}

bool Tokenizer::HandleLiterals(unsigned int helperStateGroup){
	
    if (helperStateGroup == TokenizerState_InLiteral)
    {

        if (escapeNext == true)
        {
            charBuffer.push_back(c);
            escapeNext = false;
        
            return true;
        }
        
        if (c == '\\')
        {
            escapeNext = true;
                
            return true;
        }        
        
        
        
        //. in number
        if (c == '.' && (state == TokenizerState::InInteger || state == TokenizerState::InDecimal))
        {
            state == TokenizerState::InDecimal;
            charBuffer.push_back('.');
        
            return true;
        }
        
        //Handle strings
        //exit or push
        if(
        state == TokenizerState::InStringQuote ||
        state == TokenizerState::InStringDoubleQuote ||
        state == TokenizerState::InStringBacktick
        ){
            
            //Exit string if correct quote encountered
            if (
            (state == TokenizerState::InStringQuote && c == '\'') ||
            (state == TokenizerState::InStringDoubleQuote && c == '"') ||
            (state == TokenizerState::InStringBacktick && c == '`')
            ){
                tP->AddLiteralString(this);
                state = TokenizerState::Normal;
            }
            //If still in string, add char
            else
                charBuffer.push_back(c);
        
            return true;   
        }
        //Enter string?
        else if (state == TokenizerState::Normal && C("'\"`")) /////////Quotes IGNORED in literals other than string
        {
            tP->AddIdentifier(this);

            if (c == '\'')
                state = TokenizerState::InStringQuote;
            else if (c == '"')
                state = TokenizerState::InStringDoubleQuote;
            else
                state = TokenizerState::InStringBacktick;

        }
        
    }
    
    return false;
}

bool Tokenizer::HandleSpecial(unsigned int helperStateGroup){
	if (pc == ':' || pc == '=' || pc == '^')
    {
        if (pc == ':')
        {
            if (c == ':')
                tP->AddToken(this, TokenType::Assignment);
            else
                tP->AddToken(this, TokenType::AssignmentPush);
    
        }
        else if (pc == '=')
        {
            if (c == ':')
                tP->AddToken(this, TokenType::PointerAssignment);
            else
                tP->AddToken(this, TokenType::PointerAssignmentPush);
    
            //tP->AddToken(this, TokenType::);
            
        }
        else if (pc == '^')
        {
            if (c == ':')
                tP->AddToken(this, TokenType::UpAssignment);
            else
                tP->AddToken(this, TokenType::UpAssignmentPush);
    
            
        }
        
        return true;
    }
    
    return false;
}

bool Tokenizer::HandleFeedChar(unsigned int helperStateGroup){
	
    if (helperStateGroup == TokenizerState_Normal)
    {
    	
    			
    	
        if (isspace(c))
        {
            if (!isspace(pc)) //Ignore double spaces
            {
                //Push identifier to stream
                tP->AddIdentifier(this);                	
                
                return true;
            }
        }
        else if(c == ',')
        {
                //Push identifier to stream
                tP->AddIdentifier(this);                	
                
                return true;
        }
        else if (C("([{.")) //complex opening
        {
            
            tP->AddIdentifier(this);

            if (c == '(')
                tP->AddToken(this, TokenType::Parenthesized);
            else if (c == '[')
                tP->AddToken(this, TokenType::Bracketed);
            else if (c == '{')
                tP->AddToken(this, TokenType::Braced);
            else if (c == '.')
                tP->AddToken(this, TokenType::Dotted);

            tokenTreeStack.push_back(0); //Add complex to stack
            tP->AddToken(this, {(size_t)0});       //Tree size, changed on tree end
            
            return true;
            
        }
        else if (C(")]}")) //complex closing
        {
            tP->AddIdentifier(this);
            std::size_t treeLength = tokenTreeStack.back();
            tokenTreeStack.pop_back();
            tP->tokens[tP->tokens.size() - treeLength] = {treeLength}; //Insert tree size
        
            return true;
        
        }
        else if (c == '$')
        {
            if (IsValidIdentifierChar(charBuffer[0])) //part of identifier?
                charBuffer.push_back(c);
            else
            {
                tP->AddIdentifier(this);
                state = TokenizerState::InIdentifier;
            }
            
            return true;
        }
        else if (isdigit(c))
        {
            if (IsValidIdentifierChar(charBuffer[0])) //identifier with numbers?
                charBuffer.push_back(c);
            else
                state = TokenizerState::InInteger;
                
            return true;
        }
        else if (c == ';')
        {
            //:; =; ^;
            
            tP->AddIdentifier(this);
            tP->AddToken(this,TokenType::Pop);
        
        
            return true;
        }
        
        
        
        if (c == '\0')
        {
            //END OF FILE
            tP->AddIdentifier(this);
        	return true;
        
        }
        
    }

    charBuffer.push_back(c);

    return true;
}

void Tokenizer::FeedChar()
{
    unsigned int helperStateGroup = GetTokenizerStateGroup(state);

    if(
    HandleSpecial(helperStateGroup) == false &&
    HandleComments(helperStateGroup) == false &&
    HandleLiterals(helperStateGroup) == false &&
    HandleFeedChar(helperStateGroup) == false
    ){
        //Ignore, needs more chars to decide what to do
    }
			
    
}

TokenPack::TokenPack(const std::string &code)
{

    std::cout << "\nCode:'\n" << code << "'\n\n"; /////////////////////


    Tokenizer *t = new Tokenizer(this);

    for (char const &c : code)
    {
        t->pc = t->c;
        t->c = c;
        t->FeedChar();
    }

    t->pc = ' ';
    t->c = '\0';
    t->FeedChar();

    delete t;
}

/*
Separators:
Trailing Whitespaces often cleared / ignored
.
,
()[]{}
`"'
:=^ //sem ako prethodni znak nije isto :=^ ili prethodni !~
#
&|
$
;~ //Sem ako sledeci znak nije =
@
*/