#ifndef File2Code_H
#define File2Code_H


class File2Code
{
public:
  typedef enum GenModeType{JAVA, CPP};

protected:
  std::string m_name;
  std::string m_infname;
  GenModeType m_mode;
protected:
  void genJavaTail(std::ostream& out);
  void genJavaHeader(std::ostream& out);
  void genCppHeader(std::ostream& out);
  void genCppTail(std::ostream& out);
  void genBody(std::ostream& out);
  void genJava(std::ostream& out);
  void genCpp(std::ostream& out);
  void replace(std::string& out,
                        const std::string& str,
                        const std::string& s1,
                        const std::string& s2);


public:
  File2Code(const std::string& name, 
                    const std::string& infname, 
                    const GenModeType& mode);
  void gen(std::ostream& out);
  ~File2Code(void);
};

#endif //File2Code
