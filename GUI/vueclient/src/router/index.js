import Vue from 'vue'
import Router from 'vue-router'
import home from '@/components/home'

import mainsearch from '@/components/mainsearch'
import labone from '@/components/labone'
import labhome from '@/components/labhome'
import labtwo from '@/components/labtwo'
import labthree from '@/components/labthree'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/', //网站主页
      name: 'Home',
      component: home,
      children:[
        {
          path: '/',
          component: labhome,
        },
        {
          path: 'mainsearch',
          component: mainsearch,
        },
        {
          path: 'labone',
          component: labone,
        },
        {
          path: 'labtwo',
          component: labtwo,
        },
        {
          path: 'labthree',
          component: labthree,
        }
      ]
    },
  ]
})
