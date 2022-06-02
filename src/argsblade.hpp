/**
 * @file      argsblade.hpp
 *
 * @brief     ������Ƭ���ļ�
 *
 * @details   ���ڷָ������ڲ���
 *
 * @author    XiaoLey(xiao.ley\@outlook.com)
 *
 * @date      2022-06-02
 *
 * @version   1.0
 **********************************************************************************
 *
 * @attention
 * Ӳ��ƽ̨: Windows \n
 * SDK�汾:
 *
 * @par �޸���־:
 * <table>
 * <tr><th>Date         <th>Version  <th>Author   <th>Description</tr>
 * <tr><td>2022-06-02   <td>1.0      <td>XiaoLey  <td>������ʼ�汾</tr>
 * </table>
 *
 **********************************************************************************
 */

#ifndef ARGSBLADE_ARGSBLADE_HPP
#define ARGSBLADE_ARGSBLADE_HPP

#include <string>
#include <map>
#include <vector>

namespace ArgsBlade
{
    using ArgVec = std::vector<std::string>;        ///< Type����������
    using ArgTb = std::map<std::string, ArgVec>;    ///< Type��������

    /**
     * @brief   ��Ƭ�࣬�����и�
     *
     * @note    ���ַ���("")��ʾ����ֱ�������飬Ҳ������Щ����ֵ�������κεı�ʶ��
     *
     * @par �޸���־
     * <table>
     * <tr><th>Date              <th>Author  <th>Description
     * <tr><td>2022-06-02 10:50  <td>XiaoLey <td>������
     * </table>
     */
    class Blade
    {
    public:
        Blade(int argc, const char *const argv[]);
        Blade(int argc, const char *const argv[], const ArgVec &argSign);

        /// ͨ��������ʶ�ڲ��������Ҵ���Ӧ�Ĳ�����
        const ArgVec &operator[](const std::string &sign) const;

        /// ���ò�����ʶ
        Blade &setSigns(const ArgVec &argSign);

        /// �ָ����
        void slicing();

        /// �жϲ���ֵ�Ƿ������ָ���Ĳ�����ʶ�У����������ʶΪ�գ���Ϊ�ޱ�ʶ�Ĳ���ֵ��
        [[nodiscard]]
        bool contains(const std::string &sign, const std::string &arg) const;

        /// �ж�ָ���Ĳ�����ʶ���Ƿ����
        [[nodiscard]]
        bool containsSign(const std::string &sign) const;

        /// ��ȡ������������������ʶ����
        [[nodiscard]]
        size_t getArgCount() const;

        /// ��ȡֱ���������������������κα�ʶ����
        [[nodiscard]]
        size_t getDirectArgCount() const;

        /// ��ȡ��ʶ��ʵ������
        [[nodiscard]]
        size_t getSignRealCount() const;

    private:
        ArgVec m_argSign;           ///< ������ʶ
        ArgTb m_args;               ///< ������
        int m_argc;                 ///< ��������
        const char *const *m_argv;  ///< ����ֵ��
    };


    Blade::Blade(int argc, const char *const argv[]) :
      m_argc(argc),
      m_argv(argv)
    {
        if (m_argc < 2)
            return;
    }


    Blade::Blade(int argc, const char *const argv[], const ArgVec &argSign) :
      m_argc(argc),
      m_argv(argv),
      m_argSign(argSign)
    {
        if (m_argc < 2)
            return;
    }


    const ArgVec &Blade::operator[](const std::string &sign) const
    {
        return m_args.at(sign);
    }


    Blade &Blade::setSigns(const ArgVec &argSign)
    {
        m_argSign = argSign;
        return *this;
    }


    void Blade::slicing()
    {
        if (m_argc < 2)
            return;

        if (m_argSign.empty()) {
            ArgVec vec;
            for (int i = 1; i < m_argc; ++i) {
                vec.emplace_back(*(m_argv + i));
            }

            m_args.insert(std::make_pair("", std::move(vec)));
            return;
        }

        m_args[""] = ArgVec();
        const char *sign = "";
        for (int i = 1; i < m_argc; ++i) {
            auto &arg = *(m_argv + i);

            if (std::find(m_argSign.begin(), m_argSign.end(), arg) != m_argSign.end()) {
                if (m_args.find(arg) == m_args.end())
                    m_args[arg] = ArgVec();

                sign = arg;
                continue;
            }

            m_args[sign].emplace_back(arg);
        }
    }


    bool Blade::contains(const std::string &sign, const std::string &arg) const
    {
        return m_args.find(sign) != m_args.end()
               && std::find(m_args.at(sign).begin(), m_args.at(sign).end(), arg) != m_args.at(sign).end();
    }


    bool Blade::containsSign(const std::string &sign) const
    {
        return m_args.find(sign) != m_args.end();
    }


    size_t Blade::getArgCount() const
    {
        size_t count = 0;
        for (const auto &i : m_args) {
            count += i.second.size();
        }

        return count;
    }


    size_t Blade::getSignRealCount() const
    {
        if (m_args.find("") != m_args.end())
            return m_args.size() - 1;
        else
            return m_args.size();
    }


    size_t Blade::getDirectArgCount() const
    {
        if (m_args.find("") == m_args.end())
            return 0;

        return m_args.at("").size();
    }
}

#endif //ARGSBLADE_ARGSBLADE_HPP
