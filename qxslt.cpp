#include <QCoreApplication>
#include <QXmlQuery>
#include <QFile>
#include <QBuffer>
#include <iostream>

int main(int ac, char ** av) 
{
  if (ac < 2) {
    std::cerr << av[0] << " file.xml [file.xsl]\n";
    return 1;
  }
  QCoreApplication app(ac, av);
  
  QXmlQuery query(QXmlQuery::XSLT20);
  query.setFocus(QUrl(av[1]));
  
  int err = 0;
  QByteArray xsl_array = [&]() {
    QString xsl_name;
    if (ac == 3) {
      xsl_name = av[2];
    }
    else {
      xsl_name = av[1];
      if (xsl_name.size() > 3) {
        xsl_name[xsl_name.size() - 2] = 's';
      }
      else {
        xsl_name += ".xsl";
      }
    }
    
    QFile xsl_file(xsl_name);
    if (!xsl_file.open(QIODevice::ReadOnly)) {
      std::cerr << av[0] << ": " << xsl_name.toStdString() << ": unknow xsl file.\n";
      err = 2;
      return QByteArray{};
    }

    return xsl_file.readAll();
  }();
  
  if (err) {
    return err;
  }
  
  xsl_array.replace("xmlns=\"http://www.w3.org/1999/xhtml\"", "");
  xsl_array.replace("<html  xml:lang=\"fr\">", "<html>");
  xsl_array.replace("<html xml:lang=\"fr\">", "<html>");
  
  QBuffer xsl_buf(&xsl_array);
  xsl_buf.open(QIODevice::ReadOnly);
  query.setQuery(&xsl_buf);
  
  QFile out;
  out.open(stdout, QIODevice::WriteOnly);
  if (!query.evaluateTo(&out)) {
    return 3;
  }
  
  return 0;
}
