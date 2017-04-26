template< typename CharT, typename Traits >
static std::basic_istream<CharT, Traits>&
operator_text_to_interval(std::basic_istream<CharT, Traits>& is,
        $T$& x)
{
    int state = (is.flags() & std::ios_base::skipws) ? 0 : 1;
    std::string input;
    while (is && state != 99 && state != 100)
    {
       char ch;
       try
       {
           ch = is.peek();
       }
       catch (std::ios_base::failure& e)
       {
           if (!is.eof())
           {
               throw;
           }
           ch = '\0';
       }
       if (is.eof() || ch == '\n')
       {
           state = state == 3 || state == 5 || state == 6 || state == 7 || state == 8 || state == 11 ? 100 : 99;
           break;
       }
       switch (state)
       {
          case 0:
              if (std::isspace(ch))
              {
                 is.get();
                 break;
              }
          case 1:
              if (ch == '[') state = 2;
              else if (ch == '+' || ch == '-' || ch == '.' || std::isdigit(ch)) state = 4;
              else { state = 99; break; }
              input += ch;
              is.get();
              break;
          case 2:
              if (ch == ']') state = 3;
              input += ch;
              is.get();
              break;
           case 3:
              if (ch == '_') state = 12;
              else { state = 100; break; } 
              input += ch;
              is.get();
              break;
           case 4:
              if (ch == '?') state = 5;
              input += ch;
              is.get();
              break;
           case 5:
              if (std::isdigit(ch)) state = 6;
              else if (ch == '?') state = 7;
              else if (ch == 'd' || ch == 'D' || ch == 'u' || ch == 'U') state = 8;
              else if (ch == 'e' || ch == 'E') state = 9;
              else if (ch == '_') state = 12;
              else { state = 100; break; }
              input += ch;
              is.get();
              break;
           case 6:
              if (std::isdigit(ch)) state = 6;
              else if (ch == 'd' || ch == 'D' || ch == 'u' || ch == 'U') state = 8;
              else if (ch == 'e' || ch == 'E') state = 9;
              else if (ch == '_') state = 12;
              else { state = 100; break; }
              input += ch;
              is.get();
              break;
           case 7:
              if (ch == 'd' || ch == 'D' || ch == 'u' || ch == 'U') state = 8;
              else if (ch == 'e' || ch == 'E') state = 9;
              else if (ch == '_') state = 12;
              else { state = 100; break; }
              input += ch;
              is.get();
              break;
           case 8:
              if (ch == 'e' || ch == 'E') state = 9;
              else if (ch == '_') state = 12;
              else { state = 100; break; }
              input += ch;
              is.get();
              break;
           case 9:
              if (ch == '+' || ch == '-') state = 10;
              else if (std::isdigit(ch)) state = 11;
              else { state = 99; break; }
              input += ch;
              is.get();
              break;
           case 10:
              if (std::isdigit(ch)) state = 11;
              else { state = 99; break; }
              input += ch;
              is.get();
              break;
           case 11:
              if (std::isdigit(ch)) state = 11;
              else if (ch == '_') state = 12;
              else { state = 100; break; }
              input += ch;
              is.get();
              break;
           case 12:
              state = 13;
              input += ch;
              is.get();
              break;
           case 13:
              state = 14;
              input += ch;
              is.get();
              break;
           case 14:
              state = 100;
              input += ch;
              is.get();
              break;
       }
    }
    if (is && state == 100)
    {
        $T$ r;
        p1788::exception::exception_bits saved_cwd = p1788::exception::cwd();
        p1788::exception::set_throw_exception_cwd(p1788::exception::exception_bits::none_bit);
        p1788::exception::exception_bits saved_state = p1788::exception::state();
        p1788::exception::clear();
        r = $G$(input);
        p1788::exception::exception_bits new_state = p1788::exception::state();
        p1788::exception::state() = saved_state;
        p1788::exception::set_throw_exception_cwd(saved_cwd);
        if (new_state == p1788::exception::exception_bits::none_bit)
        {
            x = r;
        }
        else
        {
            is.setstate(std::ios_base::failbit);
            if (new_state & p1788::exception::exception_bits::undefined_operation_bit)
                p1788::exception::signal_undefined_operation();
            if (new_state & p1788::exception::exception_bits::possibly_undefined_operation_bit)
                p1788::exception::signal_possibly_undefined_operation();
        }
/*        
        int exc = $G$;
        signal_exception(exc);
        if (exc >= 0)
            x = r;
        else
            is.setstate(std::ios_base::failbit);
 */
    }
    else {
        is.setstate(std::ios_base::failbit);
    }
    return is;
}

