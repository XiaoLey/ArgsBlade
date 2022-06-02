/**
 * @file      argsblade.hpp
 *
 * @brief     参数刀片类文件
 *
 * @details   用于分割程序入口参数
 *
 * @author    XiaoLey(xiao.ley\@outlook.com)
 *
 * @date      2022-06-02
 *
 * @version   1.0
 **********************************************************************************
 *
 * @attention
 * 硬件平台: Windows \n
 * SDK版本:
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date         <th>Version  <th>Author   <th>Description</tr>
 * <tr><td>2022-06-02   <td>1.0      <td>XiaoLey  <td>创建初始版本</tr>
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
    using ArgVec = std::vector<std::string>;        ///< Type：参数容器
    using ArgTb = std::map<std::string, ArgVec>;    ///< Type：参数表

    /**
     * @brief   刀片类，用于切割
     *
     * @note    空字符串("")表示程序直属参数组，也就是这些参数值不输于任何的标识符
     *
     * @par 修改日志
     * <table>
     * <tr><th>Date              <th>Author  <th>Description
     * <tr><td>2022-06-02 10:50  <td>XiaoLey <td>创建类
     * </table>
     */
    class Blade
    {
    public:
        Blade(int argc, const char *const argv[]);
        Blade(int argc, const char *const argv[], const ArgVec &argSign);

        /// 通过参数标识在参数表中找处相应的参数组
        const ArgVec &operator[](const std::string &sign) const;

        /// 设置参数标识
        Blade &setSigns(const ArgVec &argSign);

        /// 分割参数
        void slicing();

        /// 判断参数值是否存在于指定的参数标识中（如果参数标识为空，则为无标识的参数值）
        [[nodiscard]]
        bool contains(const std::string &sign, const std::string &arg) const;

        /// 判断指定的参数标识符是否存在
        [[nodiscard]]
        bool containsSign(const std::string &sign) const;

        /// 获取参数数量（不包含标识符）
        [[nodiscard]]
        size_t getArgCount() const;

        /// 获取直属参数数量（即不属于任何标识符）
        [[nodiscard]]
        size_t getDirectArgCount() const;

        /// 获取标识符实际数量
        [[nodiscard]]
        size_t getSignRealCount() const;

    private:
        ArgVec m_argSign;           ///< 参数标识
        ArgTb m_args;               ///< 参数表
        int m_argc;                 ///< 参数数量
        const char *const *m_argv;  ///< 参数值串
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
