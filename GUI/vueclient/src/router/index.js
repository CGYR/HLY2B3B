import Vue from 'vue'
import Router from 'vue-router'
import home from '@/components/home'

import mainsearch from '@/components/mainsearch'
import labone from '@/components/labone'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/', //网站主页
      name: 'Home',
      component: home,
      children:[
        {
          path: 'mainsearch',
          component: mainsearch,
        },
        {
          path: 'labone',
          component: labone,
        }
      ]
    },
  ]
})
