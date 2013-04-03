/*
 * TIFactory.hh
 *
 *  Created on: Jan 2, 2013
 *      Author: nsoblath
 *
 *      Type-Indexed Factory and Registrars
 */

#ifndef TIFACTORY_HH_
#define TIFACTORY_HH_

#include "Singleton.h"

#include <iostream>
#include <map>
#include <typeinfo>

namespace rootplotter
{

    template< class XBaseType >
    class TIFactory;

    template< class XBaseType >
    class TIRegistrar
    {
        public:
            TIRegistrar() {}
            virtual ~TIRegistrar() {}

        public:
            friend class TIFactory< XBaseType >;

        protected:
            virtual XBaseType* Create() const = 0;

    };

    template< class XBaseType, class XDerivedType >
    class DerivedTIRegistrar : public TIRegistrar< XBaseType >
    {
        public:
            DerivedTIRegistrar();
            virtual ~DerivedTIRegistrar();

        protected:
            void Register() const;

            XBaseType* Create() const;

    };


    template< class XBaseType >
    class TIFactory : public Singleton< TIFactory< XBaseType > >
    {
        public:
            struct CompareTypeInfo
            {
                bool operator() (const std::type_info* lhs, const std::type_info* rhs)
                {
                    return lhs->before(*rhs);
                }
            };

        public:
            typedef std::map< const std::type_info*, const TIRegistrar< XBaseType >* > FactoryMap;
            typedef typename FactoryMap::value_type FactoryEntry;
            typedef typename FactoryMap::iterator FactoryIt;
            typedef typename FactoryMap::const_iterator FactoryCIt;

        public:
            template< class XDerivedType >
            XBaseType* Create();

            XBaseType* Create(const FactoryCIt& iter);

            template< class XDerivedType >
            void Register(const TIRegistrar< XBaseType >* registrar);

            FactoryCIt GetFactoryMapBegin() const;
            FactoryCIt GetFactoryMapEnd() const;

        protected:
            FactoryMap* fMap;


        protected:
            friend class Singleton< TIFactory >;
            friend class Destroyer< TIFactory >;
            TIFactory();
            ~TIFactory();
    };

    template< class XBaseType >
    template< class XDerivedType >
    XBaseType* TIFactory< XBaseType >::Create()
    {
        FactoryCIt it = fMap->find(&typeid(XDerivedType));
        if (it == fMap->end())
        {
            std::cerr <<  "ERROR (TIFactory::Create): Did not find factory with type <" << typeid(XDerivedType).name() << ">." << std::endl;
            return NULL;
        }

        return it->second->Create();
    }

    template< class XBaseType >
    XBaseType* TIFactory< XBaseType >::Create(const FactoryCIt& iter)
    {
        return iter->second->Create();
    }

    template< class XBaseType >
    template< class XDerivedType >
    void TIFactory< XBaseType >::Register(const TIRegistrar< XBaseType >* registrar)
    {
        FactoryCIt it = fMap->find(&typeid(XDerivedType));
        if (it != fMap->end())
        {
            std::cerr <<  "ERROR (TIFactory::Create):Already have factory registered for type <" << typeid(XDerivedType).name() << ">." << std::endl;
            return;
        }
        fMap->insert(std::pair< const std::type_info*, const TIRegistrar< XBaseType >* >(&typeid(XDerivedType), registrar));
#ifdef DEBUG
        std::cout <<  "(TIFactory::Create): Registered a factory for class type " << typeid(XDerivedType).name() << ", factory #" << fMap->size()-1 << std::endl;
#endif
    }

    template< class XBaseType >
    TIFactory< XBaseType >::TIFactory() :
        fMap(new FactoryMap())
    {}

    template< class XBaseType >
    TIFactory< XBaseType >::~TIFactory()
    {
        delete fMap;
    }

    template< class XBaseType >
    typename TIFactory< XBaseType >::FactoryCIt TIFactory< XBaseType >::GetFactoryMapBegin() const
    {
        return fMap->begin();
    }

    template< class XBaseType >
    typename TIFactory< XBaseType >::FactoryCIt TIFactory< XBaseType >::GetFactoryMapEnd() const
    {
        return fMap->end();
    }




    template< class XBaseType, class XDerivedType >
    DerivedTIRegistrar< XBaseType, XDerivedType >::DerivedTIRegistrar() :
            TIRegistrar< XBaseType >()
    {
        Register();
    }

    template< class XBaseType, class XDerivedType >
    DerivedTIRegistrar< XBaseType, XDerivedType >::~DerivedTIRegistrar()
    {}

    template< class XBaseType, class XDerivedType >
    void DerivedTIRegistrar< XBaseType, XDerivedType >::Register() const
    {
        TIFactory< XBaseType >::GetInstance()->template Register<XDerivedType>(this);
        return;
    }

    template< class XBaseType, class XDerivedType >
    XBaseType* DerivedTIRegistrar< XBaseType, XDerivedType >::Create() const
    {
        return dynamic_cast< XBaseType* >(new XDerivedType());
    }


} /* namespace Katydid */
#endif /* TIFACTORY_HH_ */
