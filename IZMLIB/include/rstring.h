/*!
  @file  rstring.h
  @brief RString�N���X�̃w�b�_�t�@�C��
*/
#ifndef IZM_RSTRING_H
#define IZM_RSTRING_H

#include <string>
#include <vector>

namespace izm
{

class RString : public std::string
{
// �R���X�g���N�^�E�f�X�g���N�^
public:
    RString();
    explicit RString( const double num );
    RString( const std::string& str );

    virtual ~RString();

// ���Z�q
public:
    // ������Z�q
    RString& operator =( const std::string& rhs );
    RString& operator =( const RString& rhs );

    // ���Z���Z�q
    RString operator +( const double rhs );

// ����
public:
    // �^�ϊ�
    int to_i() const;
    int toInt() const;
    double to_f() const;
    double toDouble() const;
    std::string to_s() const;
    std::string toStdString() const;

    // �A�N�Z�X
    char first() const;
    char last() const;

    // ����
    bool include( const std::string& str ) const;

    // ����
    std::vector<RString> split( const std::string& delimiter = " " ) const;

    // ���s�R�[�h�̍폜
    RString  chomp() const;
    RString& chomp_d();     // �j�󃁃\�b�h

    // ���������̍폜
    RString  chop() const;
    RString& chop_d();      // �j�󃁃\�b�h

    // �󔒗ޕ����̍폜
    RString  strip() const;
    RString& strip_d();     // �j�󃁃\�b�h

    RString  lstrip() const;
    RString& lstrip_d();    // �j�󃁃\�b�h

    RString  rstrip() const;
    RString& rstrip_d();    // �j�󃁃\�b�h

    // strip, lstrip, rstrip�̕ʖ����\�b�h
    RString  trim() const;
    RString& trim_d();      // �j�󃁃\�b�h

    RString  ltrim() const;
    RString& ltrim_d();     // �j�󃁃\�b�h

    RString  rtrim() const;
    RString& rtrim_d();     // �j�󃁃\�b�h

    // ������̍폜
    RString  remove( const std::string& str ) const;
    RString& remove_d( const std::string& str );     // �j�󃁃\�b�h

    // ������̒u��
    RString  sub( const std::string& before, const std::string& after ) const;
    RString& sub_d( const std::string& before, const std::string& after );      // �j�󃁃\�b�h

    RString  gsub( const std::string& before, const std::string& after ) const;
    RString& gsub_d( const std::string& before, const std::string& after );     // �j�󃁃\�b�h

    // �啶�� <=> ������
    RString  upcase() const;
    RString& upcase_d();        // �j�󃁃\�b�h

    RString  downcase() const;
    RString& downcase_d();      // �j�󃁃\�b�h
};

} // namcespace izm

#endif // IZM_RSTRING_H
