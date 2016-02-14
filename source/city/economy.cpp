// This file is part of CaesarIA.
//
// CaesarIA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CaesarIA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2013 Gregoire Athanase, gathanase@gmail.com
// Copyright 2012-2014 Dalerank, dalerankn8@gmail.com

#include "economy.hpp"
#include "city.hpp"
#include "game/player.hpp"
#include "statistic.hpp"
#include "objects/house.hpp"
#include "objects/forum.hpp"
#include "objects/senate.hpp"
#include "objects/fort.hpp"
#include "game/difficulty.hpp"
#include "events/showinfobox.hpp"

using namespace events;

namespace city
{

Economy::Economy() : econ::Treasury()
{
}

Economy::~Economy() {}

void Economy::payWages(PlayerCityPtr city)
{
  int wages = city->statistic().workers.monthlyWages();

  if( haveMoneyForAction( wages ) )
  {
    HouseList houses = city->statistic().houses.find();

    //usual workers wages
    float salary = city->statistic().workers.monthlyOneWorkerWages();
    float wages = 0;
    for( auto house : houses )
    {
      int workers = house->hired();
      float house_wages = salary * workers;
      house->appendMoney( house_wages );
      wages += house_wages;
    }

    //soldiers wages
    if( city->getOption( PlayerCity::soldiersHaveSalary ) )
    {
      FortList forts = city->statistic().military.forts();
      for( auto fort : forts )
      {
        int soldierType = fort->workerType();

        int yearSalary = city->treasury().workerSalary( soldierType );
        int monthSalary = yearSalary / (10.f * DateTime::monthsInYear);
        wages += monthSalary * fort->soldiers_n();
      }
    }

    resolveIssue( econ::Issue( econ::Issue::workersWages, ceil( -wages ) ) );
  }
  else
  {
    // TODO affect citizen sentiment for no payment and request money to caesar.
  }
}

void Economy::collectTaxes(PlayerCityPtr city)
{
  float lastMonthTax = 0;

  if( city->getOption( PlayerCity::housePersonalTaxes ) )
  {
    ForumList forums = city->statistic().objects.find<Forum>( object::forum );
    for( auto forum : forums ) { lastMonthTax += forum->takeMoney(); }

    SenateList senates = city->statistic().objects.find<Senate>( object::senate );
    for( auto senate : senates ) { lastMonthTax += senate->takeMoney(); }
  }
  else
  {
    HouseList houses = city->statistic().houses.all();
    for( auto house : houses )
    {
      //collect money only from taxed houses
      if( house->getServiceValue( Service::forum ) > 0 )
      {
        lastMonthTax += house->collectTaxes();
      }
    }
  }

  resolveIssue( econ::Issue( econ::Issue::taxIncome, lastMonthTax ) );
}

void Economy::payMayorSalary(PlayerCityPtr city)
{
  if( money() > 0 )
  {
    int playerSalary = city->mayor()->salary();
    resolveIssue( econ::Issue( econ::Issue::playerSalary, -playerSalary ) );
    city->mayor()->appendMoney( playerSalary );
  }
}

void Economy::resolveIssue(econ::Issue issue)
{
  checkIssue( issue.type );
  Treasury::resolveIssue( issue );
}

void Economy::checkIssue(econ::Issue::Type type)
{
  switch( type )
  {
  case econ::Issue::overdueEmpireTax:
  {
    int lastYearBrokenTribute = getIssueValue( econ::Issue::overdueEmpireTax, econ::Treasury::lastYear );
    std::string text = lastYearBrokenTribute > 0
        ? "##for_second_year_broke_tribute##"
        : "##current_year_notpay_tribute_warning##";

    events::dispatch<ShowInfobox>( "##tribute_broken_title##", text );
  }
  break;

  default:
  break;

  }
}

}
